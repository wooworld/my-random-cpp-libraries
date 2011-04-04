<?php

/**
 * file: populate.php
 * brief: populates the database with some information
 */
 
include "includes/functions.php";
//include "includes/config.php";

//Connect to the database
my_mysql_connect();

//Delete all previous records in company table.
//my_trusted_mysql_query( "DELETE FROM COMPANY" );
my_trusted_mysql_query( "DELETE FROM EVENT" );
//my_trusted_mysql_query( "DELETE FROM CLASS_PARTICIPANT" );

//The array that stores each INSERT query as an element. 
//Can run through them in a loop later, easy-peasy
$population = array(
/*
"INSERT INTO COMPANY (Email, Name, Address, City, State, Zip)
VALUES ('awesome@maelstrom.com', 'Maelstrom', '321 Money Ln', 'Rolla', 'MO', 64014)",
"INSERT INTO COMPANY (Email, Name, Address, City, State, Zip)
VALUES ('mage_killer@maelstrom.com', 'Mage_Killer', '456 Rock Face Rd', 'Middle-earth', 'TX', 22215)",
"INSERT INTO COMPANY (Email, Name, Address, City, State, Zip)
VALUES ('br@maelstrom.com', 'br?', 'Dirt Road', 'Brazil', 'BR', 11111)",
"INSERT INTO COMPANY (Email, Name, Address, City, State, Zip)
VALUES ('efsie@maelstrom.com', 'Efsie', 'Rich Pl', 'Gojira', 'JP', 01235)",
*/
"INSERT INTO EVENT (Event_Name, Start_Date, End_Date, Start_Time, End_Time, Comments, E_Type, S_Type, Session_Length)
VALUES ('TESTEVENT1', 1234, 5678, 2345, 6789, 'COMMENTS FOR TEST EVENT 1', 'c', 'Blood Pressure', 10)"

//"INSERT INTO COMPANY ( blah blah blah all the fields)
//VALUES ('blah blah', 'blah blah', 'blah.')"
);

//Perform the queries, huzzah
foreach ($population as $query) 
{ 
  echo "> " . $query . "<br />";
  my_trusted_mysql_query($query); 
}

//Confirm the insertions
display_results(my_trusted_mysql_query( "SELECT * FROM EVENT" ));
//display_results(my_trusted_mysql_query( "SELECT * FROM CLASS_PARTICPANT" );

//Close connection to database
my_mysql_close();

?> 