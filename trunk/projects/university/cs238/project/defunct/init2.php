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

echo "altering held in<br />";
my_trusted_mysql_query("ALTER TABLE HELD_IN ADD FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE");

echo "altering c_attend<br />";
my_trusted_mysql_query("ALTER TABLE C_ATTEND ADD FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE");
my_trusted_mysql_query("ALTER TABLE C_ATTEND ADD FOREIGN KEY (Email) REFERENCES CLASS_PARTICIPANT(Email) ON DELETE CASCADE");

echo "altering s_attend<br />";
my_trusted_mysql_query("ALTER TABLE S_ATTEND ADD FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE");
my_trusted_mysql_query("ALTER TABLE S_ATTEND ADD FOREIGN KEY (Email) REFERENCES SCREEN_PARTICIPANT(Email) ON DELETE CASCADE");

echo "altering teach<br />";
my_trusted_mysql_query("ALTER TABLE TEACH ADD FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE");
my_trusted_mysql_query("ALTER TABLE TEACH ADD FOREIGN KEY (Email) REFERENCES STAFF(Email) ON DELETE CASCADE");

echo "altering administer<br />";
my_trusted_mysql_query("ALTER TABLE ADMINISTER ADD FOREIGN KEY (Event_ID) REFERENCES EVENT(Event_ID) ON DELETE CASCADE");
my_trusted_mysql_query("ALTER TABLE ADMINISTER ADD FOREIGN KEY (Email) REFERENCES STAFF(Email) ON DELETE CASCADE");

//Close connection to database
my_mysql_close();

?> 