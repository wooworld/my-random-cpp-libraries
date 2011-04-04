<?php 

/**
 * file: init.php
 * brief: creates the database, connects to it, creates tables, populates 
 *    tables with data. ONLY RUN THIS ONE TIME!
 */

 //Note, this has been run once, all tables have been created. If a table needs
 //to be changed, please do so manually!
 
include "includes/functions.php";

//Connect to the database
my_mysql_connect();

//Stores all the queries in a single array to loop through later so I don't have
//to copy/paste the mysql_query($variable) line a gazillion times
$queries = array();

//alter table icecream modify flavor VARCHAR(35) ; 
//ALTER TABLE contacts CHANGE name name VARCHAR(80) NOT NULL;
array_push($queries, "ALTER TABLE EVENT CHANGE Start_Date Start_Date DOUBLE");
array_push($queries, "ALTER TABLE EVENT CHANGE Start_Time Start_Time DOUBLE");
array_push($queries, "ALTER TABLE EVENT CHANGE End_Date End_Date DOUBLE");
array_push($queries, "ALTER TABLE EVENT MODIFY End_Time End_Time DOUBLE");

//Perform the queries, huzzah
foreach ($queries as $query) 
{ 
  echo ">Performing " . $query . "<br />";
  my_trusted_mysql_query($query); 
}

//Close connection to database
my_mysql_close();

?> 