<?php
/**
 * file: init.php
 * brief: creates the database, connects to it, creates tables, populates 
 *    tables with data. ONLY RUN THIS ONE TIME!
 */

 //Note, this has been run once, all tables have been created. If a table needs
 //to be changed, please do so manually!
 
include "includes/functions.php";
include "includes/config.php";

//Connect to the database
my_mysql_connect();

//Stores all the queries in a single array to loop through later so I don't have
//to copy/paste the mysql_query($variable) line a gazillion times
$queries = array();

//Create the entity tables
$table_drops = array(
"DROP TABLE COMPANY CASCADE CONSTRAINTS",
"DROP TABLE COMPNAY_PHONE CASCADE CONSTRAINTS",
"DROP TABLE EVENT CASCADE CONSTRAINTS",
"DROP TABLE LOCATION CASCADE CONSTRAINTS",
"DROP TABLE CLASS_DATES CASCADE CONSTRAINTS",
"DROP TABLE CLASS_PARTICIPANT CASCADE CONSTRAINTS",
"DROP TABLE SCREEN_PARTICIPANT CASCADE CONSTRAINTS",
"DROP TABLE STAFF CASCADE CONSTRAINTS",
"DROP TABLE PERSON_PHONE CASCADE CONSTRAINTS",
"DROP TABLE HOSTS CASCADE CONSTRAINTS",
"DROP TABLE RECOMMENDS CASCADE CONSTRAINTS",
"DROP TABLE HELD_IN CASCADE CONSTRAINTS",
"DROP TABLE C_ATTEND CASCADE CONSTRAINTS",
"DROP TABLE S_ATTEND CASCADE CONSTRAINTS",
"DROP TABLE TEACH CASCADE CONSTRAINTS",
"DROP TABLE ADMINISTER CASCADE CONSTRAINTS"
);

$create_company_table = 
"CREATE TABLE COMPANY (
Email VARCHAR(50) UNIQUE NOT NULL,
Name  VARCHAR(50) NOT NULL,
Address VARCHAR(50),
City VARCHAR(50),
State CHAR(2),
Zip INT,
PRIMARY KEY (Email)
)";
array_push($queries, $create_company_table);

$create_company_phone_table = 
"CREATE TABLE COMPANY_PHONE (
Number VARCHAR(20) UNIQUE NOT NULL,
Email VARCHAR(50),
PRIMARY KEY (Number),
FOREIGN KEY (Email) REFERENCES COMPANY(Email) ON DELETE CASCADE
)";
array_push($queries, $create_company_phone_table);

$create_event_table = 
"CREATE TABLE EVENT (
Event_ID INT NOT NULL AUTO_INCREMENT, 
Event_Name VARCHAR(50),
Start_Date DOUBLE NOT NULL,
End_Date DOUBLE NOT NULL,
Start_Time DOUBLE NOT NULL,
End_Time DOUBLE NOT NULL,
Comments TEXT,
E_Type CHAR(1) NOT NULL,
S_Type VARCHAR(50),
Session_Length INT,
CONSTRAINT check_event CHECK (Start_Date>0 AND End_Date>=Start_Date),
PRIMARY KEY (Event_ID)
)";
array_push($queries, $create_event_table);

$create_location_table = 
"CREATE TABLE LOCATION (
Event_ID INT,
Location_Name VARCHAR(50) NOT NULL,
Address VARCHAR(50),
City VARCHAR(50),
State CHAR(2),
Zip INT,
Occupants INT,
CONSTRAINT check_location CHECK (Occupants>=0),
PRIMARY KEY (Event_ID, Address, City, State, Zip),
FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE
)";
array_push($queries, $create_location_table);

$create_class_dates_table = 
"CREATE TABLE CLASS_DATES (
Event_ID INT,
Days INT NOT NULL,
CONSTRAINT check_class_dates CHECK (Days>=0),
PRIMARY KEY (Event_ID),
FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE
)";
array_push($queries, $create_class_dates_table);

$create_class_participant_table = 
"CREATE TABLE CLASS_PARTICIPANT (
Email VARCHAR(50) UNIQUE NOT NULL,
Fname VARCHAR(20),
Lname VARCHAR(20),
Address VARCHAR(50),
City VARCHAR(50),
State CHAR(2),
Zip INT,
Comments TEXT,
BCBSNum INT,
BCBSSuffix INT,
Birth_Date VARCHAR(10),
PRIMARY KEY (Email)
)";
array_push($queries, $create_class_participant_table);

$create_screen_participant_table = 
"CREATE TABLE SCREEN_PARTICIPANT (
Email VARCHAR(50) UNIQUE NOT NULL,
Fname VARCHAR(20),
Lname VARCHAR(20),
Address VARCHAR(50),
City VARCHAR(50),
State CHAR(2),
Zip INT,
Comments TEXT,
Time INT,
PRIMARY KEY (Email)
)";
array_push($queries, $create_screen_participant_table);

$create_staff_table = 
"CREATE TABLE STAFF (
Email VARCHAR(50) UNIQUE NOT NULL,
Fname VARCHAR(20),
Lname VARCHAR(20),
Address VARCHAR(50),
City VARCHAR(50),
State CHAR(2),
Zip INT,
Comments TEXT,
Password VARCHAR(50) NOT NULL,
PRIMARY KEY (Email)
)";
array_push($queries, $create_staff_table);

$create_person_phone_table = 
"CREATE TABLE PERSON_PHONE (
Number VARCHAR(20) UNIQUE NOT NULL,
Email VARCHAR(50),
PRIMARY KEY (Number),
FOREIGN KEY (Email) REFERENCES CLASS_PARTICIPANT(Email) ON DELETE CASCADE
)";
array_push($queries, $create_person_phone_table);

//Create relationship tables
$create_hosts_table = 
"CREATE TABLE HOSTS (
Email VARCHAR(50),
Event_ID INT,
PRIMARY KEY (Email, Event_ID),
FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE,
FOREIGN KEY (Email) REFERENCES COMPANY(Email) ON DELETE CASCADE
)";
array_push($queries, $create_hosts_table);

$create_recommends_table = 
"CREATE TABLE RECOMMENDS (
CEmail VARCHAR(50),
SEmail VARCHAR(50),
PRIMARY KEY (CEmail, SEmail),
FOREIGN KEY (SEmail) REFERENCES STAFF(Email) ON DELETE CASCADE,
FOREIGN KEY (CEmail) REFERENCES COMPANY(Email) ON DELETE CASCADE
)";
array_push($queries, $create_recommends_table);

$create_held_in_table = 
"CREATE TABLE HELD_IN (
Event_ID INT,
Address VARCHAR(50),
PRIMARY KEY (Event_ID, Address),
FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE,
FOREIGN KEY (Address) REFERENCES LOCATION(Address) ON DELETE CASCADE
)";
array_push($queries, $create_held_in_table);

$create_c_attend_table = 
"CREATE TABLE C_ATTEND (
Event_ID INT,
Email VARCHAR(50),
PRIMARY KEY (Event_ID, Email),
FOREIGN KEY (Email) REFERENCES CLASS_PARTICIPANT(Email) ON DELETE CASCADE,
FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE,
)";
array_push($queries, $create_c_attend_table);

$create_s_attend_table = 
"CREATE TABLE S_ATTEND (
Event_ID INT,
Email VARCHAR(50),
PRIMARY KEY (Event_ID, Email),
FOREIGN KEY (Email) REFERENCES SCREEN_PARTICIPANT(Email) ON DELETE CASCADE,
FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE,
)";
array_push($queries, $create_s_attend_table);

$create_teach_table = 
"CREATE TABLE TEACH (
Event_ID INT,
Email VARCHAR(50),
PRIMARY KEY (Event_ID, Email),
FOREIGN KEY (Email) REFERENCES STAFF(Email) ON DELETE CASCADE,
FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE,
)";
array_push($queries, $create_teach_table);

$create_administer_table = 
"CREATE TABLE ADMINISTER (
Event_ID INT,
Email VARCHAR(50),
PRIMARY KEY (Event_ID, Email),
FOREIGN KEY (Email) REFERENCES STAFF(Email) ON DELETE CASCADE,
FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE,
)";
array_push($queries, $create_administer_table);

//Drop the tables to clean up after errors when generating them
foreach ($table_drops as $q)
{
  echo "Performing <br />" . $q . "<br />";
  my_trusted_mysql_query($q);
}


//Perform the queries, huzzah
foreach ($queries as $query) 
{ 
  echo "Performing \n" . $query . "\n";
  my_trusted_mysql_query($query); 
}

//Drop the tables to clean up after errors when generating them
/*foreach ($queries as $table_drops)
{
  echo "Performing <br />" . $table_drops . "<br />";
  my_trusted_mysql_query($table_drops);
}*/

//Close connection to database
my_mysql_close();
?> 