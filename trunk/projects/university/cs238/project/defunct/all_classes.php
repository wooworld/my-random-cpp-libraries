<html>
<title>
Company Test
</title>
<body>

<!-- The php script for generating the table and handling database queries -->
<?php 

include "includes/functions.php";

my_mysql_connect();
//Class
echo "<h1><CENTER>Classes</CENTER></h1>";
display_results(my_trusted_mysql_query( "SELECT * FROM EVENT WHERE E_Type = true"));
my_mysql_close();
        
?>

</body>
</html> 
