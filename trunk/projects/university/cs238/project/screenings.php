<META name="verify-v1" content="6q6waintnJ2Z4K032AMMXjPPj3/YjkWR96eHAY3rD5I=" />
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
<META NAME="Author" CONTENT="Dale Twombly">
<META NAME="Keywords" CONTENT="Group 13, Maelstrom Healthcare">
<META NAME="Description" CONTENT="Group 13's Database UI">
<META NAME="rating" content="General">
<META NAME="robots" content="All">
<META NAME="revisit-after" content="7 days">
<META NAME="distribution" content="global">
<title>Group 13 - Maelstrom Healthcare</title>
<link href="includes/style.css" rel="stylesheet" type="text/css">
<script language="JavaScript" img src="includes/functions.js"></script>

<body onLoad="MM_preloadImages('/images/index_r3_c7_f2.jpg','/images/index_r3_c9_f2.jpg','/images/index_r2_c1_f2.jpg','/images/index_r3_c1_f2.jpg','/images/index_r4_c1_f2.jpg','/images/index_r6_c1_f2.jpg','/images/index_r7_c1_f2.jpg','/images/index_r9_c1_f2.jpg','/images/index_r10_c1_f2.jpg','/images/index_r11_c1_f2.jpg','/images/index_r16_c2_f2.jpg','/images/header1.jpg','/images/header2.jpg','/images/header3.jpg','/images/header4.jpg','/images/header5.jpg','/images/header6.jpg','/images/header7.jpg','/images/header8.jpg','/images/header9.jpg','/images/header10.jpg');runSlideShow()">

<style type="text/css">
    <!--
    .style21
    {
        color: #A5A9B5;
        width: 756px;
        height: 38px;
        font-family: Sylfaen;
    }
    .style25
    {
        width: 54px;
    }
    .style26
    {
        width: 100%;
        height: 433px;
        font-family: Sylfaen;
    }
    .style27
    {
        height: 16px;
        font-size: x-small;
        width: 750px;
    }
    .style28
    {
        width: 750px;
        text-align: center;
    }
    -->
</style>
<table width="100%" height="100%"  border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td background="back.gif"><table width="800" border="0" align="center" cellpadding="0" cellspacing="0" style="border:1 solid #790000;">
      <tr>
        <td colspan="2"><div align="left" style="background-color: #1195F0">
            <a href="index.html"><img src="header-1.jpg" width="800" height="136" 
                style="border-width: 0px"></a></div></td>
      </tr>
      <tr>
        <td align="left" valign="top" 
              style="background-color: #FFFFFF" class="style25"><table align="left" border="0" cellpadding="0" cellspacing="0" width="152">
         <tr>
            <td width="152"><table width="152" border="0" align="left" cellpadding="0" cellspacing="0" bgcolor="#999999">
         <tr>
         <td width="152"><div align="left"><img src="left_bar-1.jpg" width="152" height="436"></div></td>
         </tr>
</table>
</td>
          </tr>

        </table></td>
        <td align="left" width="100%" style="21; background-color: #FFFFFF;">
            <table class="style26">
                <tr>
                    <td class="style27">
                        <a href="index.html">Home</a> &gt; <a href="screenings.php">Screenings</a><br />
                        <hr style="height: -12px; margin-top: 0px" />
                    </td>

                </tr>
                <tr>
                    <td class="style28">
                        Screenings:<br />
<?php 

    include "includes/functions.php";

    my_mysql_connect();
  
$query_results = my_trusted_mysql_query( "SELECT EVENT.Event_ID, Event_Name, Start_Date, Start_Time, End_Date, End_Time, Location_Name, Address, City, State, Zip FROM EVENT JOIN LOCATION ON (EVENT.EVENT_ID = LOCATION.EVENT_ID) WHERE E_Type = 's'");
    echo "<table border='1'>";
  echo "<tr>";
 

  //Print out the table headers
  foreach ( $query_results[0] as $key => $value )
  {
    echo "<th>$key</th>";
  }
  
  echo "</tr>";
  
  //Print out each row
  foreach ($query_results as $row) 
  {
    echo "<tr>";
    
    foreach( $row as $key => $value )
    {
      if($key == "Event_ID")
      {
        echo "<td><a href='http://group13.x10hosting.com/screening_part_manip.php'>$value</a></td>";
      }
      else
      {     
        echo "<td>$value</td>";
      }
    }
    echo "</tr>";
  }    

  echo "</table>"; 

    my_mysql_close();
    
?>
                       </td>
               </tr>
            </table>
      </tr>
      <tr>
        <td colspan="2" style="background-color: #CCCCCC"><table align="left" border="1" cellpadding="0" cellspacing="0" width="100%">
  <tr>
    <td background="/images/index_r17_c9.jpg" class="style21">
        <div align="center">Patents and Copyrights owned by Maelstrom, Not for use by others<strong>.</strong><br>
        </div></td>
  </tr>
</table>
</td>
      </tr>
    </table></td>
  </tr>
</table>
