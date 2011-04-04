<html>
<title>
Company Test
</title>
<body>

<!-- The php script for generating the table and handling database queries -->
<?php 

include "includes/functions.php";

my_mysql_connect();
echo "<h1><CENTER>Companies</CENTER></h1>";      
$total_company = count(my_trusted_mysql_query( "SELECT * FROM COMPANY"));
echo "<CENTER>$total_company</CENTER>";

my_mysql_close();
        
?>

</body>
</html> 
