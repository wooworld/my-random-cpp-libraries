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
$results_staff = my_trusted_mysql_query( "SELECT * FROM STAFF");
display_results($results_staff);
echo "<h1><CENTER>Screen Participants</CENTER></h1>";
display_results(my_trusted_mysql_query( "SELECT * FROM SCREEN_PARTICIPANT"));
echo "<h1><CENTER>Class Participants</CENTER></h1>";
display_results(my_trusted_mysql_query( "SELECT * FROM CLASS_PARTICIPANT"));

my_mysql_close();
        
?>

</body>
</html> 
