<html>
<title>
Company Test
</title>
<body>

<!-- The php script for generating the table and handling database queries -->
<?php 

include "includes/functions.php";

my_mysql_connect();
    
display_results(my_trusted_mysql_query( "SELECT * FROM COMPANY"));

my_mysql_close();
        
?>

</body>
</html> 
