<html>
<title>
Company Test
</title>
<body>

<!-- The php script for generating the table and handling database queries -->
<?php 

include "includes/functions.php";

my_mysql_connect();
echo "<h1><CENTER>Participants</CENTER></h1>";      
$total_non_staff = count(my_trusted_mysql_query( "SELECT * FROM CLASS_PARTICIPANT"))+ count(my_trusted_mysql_query( "SELECT * FROM SCREEN_PARTICIPANT"));
echo "<CENTER>$total_non_staff</CENTER>";

my_mysql_close();
        
?>

</body>
</html> 
