<html>
<title>
Company Test
</title>
<body>

<!-- The php script for generating the table and handling database queries -->
<?php 

include "includes/functions.php";

my_mysql_connect();
//Session
echo "<h1><CENTER>Sessions</CENTER></h1>";
display_results(my_trusted_mysql_query( "SELECT * FROM EVENT WHERE E_Type = false"));
my_mysql_close();
        
?>

</body>
</html> 
