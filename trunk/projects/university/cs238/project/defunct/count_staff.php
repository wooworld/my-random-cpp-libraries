<html>
<title>
Company Test
</title>
<body>

<!-- The php script for generating the table and handling database queries -->
<?php 

include "includes/functions.php";

my_mysql_connect();
echo "<h1><CENTER>Staff</CENTER></h1>";    
$total_staff = count(my_trusted_mysql_query( "SELECT * FROM STAFF"));
echo "<CENTER>$total_staff</CENTER>";

my_mysql_close();
        
?>

</body>
</html> 
