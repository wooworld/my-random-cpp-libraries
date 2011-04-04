<html>
<title>
Company Test
</title>
<body>
<h1>YEAHBUDDY YEAHBUDDY YEAHBUDDY YEAHBUDDY WE GOT THIS</h1>

<!-- The php script for generating the table and handling database queries -->
<?php 

include "includes/functions.php";

//See if the page was called with POST data, meaning this page has been called before
if (isset($_POST['submit']))
{ 
  //Check various conditions to make sure input is valid.
  if ( !preg_match('/^[a-zA-Z0-9._-]+@[a-zA-Z0-9-]+\.[a-zA-Z.]{2,5}$/', $_POST['Email']) )
  {
    echo "Invalid Email entered. Email must be in the format \"name@server.com\"<br />";
  }
  
  //Input data was valid
  else
  {  
    //Copy $_POST data, sanitizing it to prevent SQL injection attacks.
    $q = safe_inputs( $_POST );
    
    //Force zip code to a number
    $zip_num = (int)$q[Zip];
    
    my_mysql_connect();
    
    //Pick the correct query type
    if ($_POST['query_type'] == 'insert')
    {    
      //Name can't be blank on insertion
      if ($_POST['Name'] == '')
      {
        echo "Invalid Name entered. Name cannot be blank. <br />";
      }
    
      //Company is already in the database.
      else if( count( my_trusted_mysql_query("SELECT Email FROM COMPANY WHERE Email = '$q[Email]'") ) > 0 )
      {
        echo "The company with the e-mail " . $q['Email'] . " already exists in the database. " .
          "To edit this company's information, please select update instead of insert.<br /><br />";
        $_POST['Fill'] = 'true';
      } 
    
      else
      {
        //Perform the insertion
        $query = "INSERT INTO COMPANY (Email, Name, Address, City, State, Zip) 
        VALUES ('$q[Email]', '$q[Name]', '$q[Address]', '$q[City]', '$q[State]', $zip_num)";

        my_trusted_mysql_query( $query );
        
        echo "Record inserted: <br />";
        display_results(my_trusted_mysql_query( "SELECT * FROM COMPANY WHERE Email = '$q[Email]'" ));

        my_mysql_close();
        
        $_POST['Fill'] = 'false';
      }
    }
    
    else if ($_POST['query_type'] == 'update')
    {
      //Company is not in the database.
      if( count( my_trusted_mysql_query("SELECT Email FROM COMPANY WHERE Email = '$q[Email]'") ) == 0 )
      {
        echo "The company with the e-mail " . $q['Email'] . " does not exist in the database. " .
          "To add this company's information, please select insert instead of update.<br /><br />";
        $_POST['Fill'] = 'true';
      } 
    
      else
      {                
        //Makes a query to only update fields that were not left blank
        $query  = "UPDATE COMPANY SET ";
        $query .=                       "Email='$q[Email]'";
        $query .= $q['Name']    != '' ? ", Name='$q[Name]'" : "";
        $query .= $q['Address'] != '' ? ", Address='$q[Address]'" : "";
        $query .= $q['City']    != '' ? ", City='$q[City]'"       : "";
        $query .= $q['State']   != '' ? ", State='$q[State]'"     : "";
        $query .= $q['Zip']     != '' ? ", Zip='$zip_num'"        : "";
        $query .= " WHERE Email='$q[Email]'";

        echo "Old record: <br />";
        display_results( my_trusted_mysql_query( "SELECT * FROM COMPANY WHERE Email = '$q[Email]'" ));
        
        my_trusted_mysql_query( $query );
        
        echo "<br />New updated record:";
        display_results( my_trusted_mysql_query( "SELECT * FROM COMPANY WHERE Email = '$q[Email]'" ));

        my_mysql_close();
        
        $_POST['Fill'] = 'false';
      }
    }
    
    else if ($_POST['query_type'] == 'delete')
    {    
      //Company is not in the database.
      if( count( my_trusted_mysql_query("SELECT Email FROM COMPANY WHERE Email = '$q[Email]'") ) == 0 )
      {
        echo "The company with the e-mail " . $q['Email'] . " does not exist in the database. " .
          "To add this company's information, please select insert.<br /><br />";
        $_POST['Fill'] = 'true';
      } 
    
      else
      {        
        //Show the record that's about to be deleted.
        echo "Record deleted:";
        display_results( my_trusted_mysql_query( "SELECT * FROM COMPANY WHERE Email = '$q[Email]'" ));
      
        $query = "DELETE FROM COMPANY WHERE Email='$q[Email]'";
        
        my_trusted_mysql_query( $query );
        
        my_mysql_close();
        
        $_POST['Fill'] = 'false';
      }
    }
    
    else
    {
      echo "An unexpected selection has been made. <br />";
      my_mysql_close();
      die();
    }
  }
}
?>

<br />

<!--get user input-->
<hr>
Instructions when entering data:<br />
When inserting a new company, you need to supply as much information as possible about the company.<br />
When deleting a company, you need only supply the company's e-mail address and name.<br />
When updating a company's information, make sure the e-mails match, and leave any fields you do not want to change blank.<br />

<br />

<fieldset>
<legend>Company</legend>
<form action="company.php" method="POST">
<fieldset>
<legend>Select query type</legend>
<input type="radio" name="query_type" value="insert" checked="checked" />Insert a new company's information.<br />
<input type="radio" name="query_type" value="update" />Update an already inserted company's information.<br />
<input type="radio" name="query_type" value="delete" />Delete an already inserted company's information.<br />
</fieldset>
<br />
Email: <input type="text" name="Email" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Email']; 
  }
?>
" /> (xyz@abc.com)<br />
Name: <input type="text" name="Name" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Name']; 
  }
?>
" />  (Not blank)<br />
Address: <input type="text" name="Address" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true')
  {
    echo $_POST['Address']; 
  }
?>
" />  <br />
City: <input type="text" name="City" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['City'];
  }
?>
" />  <br />
State: <select name="State">
  <option value="MO">MO</option>
  <option value="TX">TX</option>
  <option value="WA">WA</option>
  <option value="EU">EU</option>
  <option value="JP">JP</option>
  <option value="AF">AF</option>
</select>  <br />
Zip: <input type="text" name="Zip" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Zip'];
  }
?>
" />  <br />
<input type="hidden" name="Fill" value="true" />
<input type="submit" name="submit" value="Do it!" />
</form>
</fieldset>

</body>
</html> 