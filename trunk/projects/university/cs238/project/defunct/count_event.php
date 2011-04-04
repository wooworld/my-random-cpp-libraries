<html>
<title>
Company Test
</title>
<body>

<!-- The php script for generating the table and handling database queries -->
<?php 

include "includes/functions.php";

my_mysql_connect();
echo "<h1><CENTER>Events</CENTER></h1>";      
$total_event = count(my_trusted_mysql_query( "SELECT * FROM EVENT"));
echo "<CENTER>$total_event</CENTER>";

my_mysql_close();
        
?>

</body>
</html> 
