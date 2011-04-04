<html>
<title>
Company Test
</title>
<body>

<!-- The php script for generating the table and handling database queries -->
<?php 

include "includes/functions.php";

my_mysql_connect();
echo "<h1><CENTER>Class</CENTER></h1>"; 
//Displays the avrage number of people attending all classes
display_results(my_trusted_mysql_query( "SELECT AVG(people) FROM ( SELECT Event_ID, count(Email) people FROM C_ATTEND GROUP BY Event_ID) AS cnt_table"));

echo "<h1><CENTER>Session</CENTER></h1>"; 
//Displays the avrage number of people attending all sessions
display_results(my_trusted_mysql_query( "SELECT AVG(people) FROM ( SELECT Event_ID, count(Email) people FROM S_ATTEND GROUP BY Event_ID) AS cnt_table"));

my_mysql_close();
        
?>

</body>
</html> 
