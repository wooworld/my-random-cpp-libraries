﻿<?php include 'sessionHandler.php'; ?>

<head>
  <title>Previous Recommendation</title>
  <?php include'style.html'; ?>
</head>
<body bgcolor="Black">
    <SPAN style="FONT-FAMILY: Arial">
        <table width="900" align="center" border="0" cellpadding="0" cellspacing="0">
            <?php include'menu.php'; ?>
                <tr><td><table width="100%" background="bg.jpg" background-attachment="fixed">
                    <tr><td width="5"></td><td>&nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">Previous Recommendation</span></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td><hr width="100%" /></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>
                      <?php
                        if ( isset($_SESSION["AcctNumber"]) )
                        {
                          echo "... <br />";
                        }
                        else
                        {
                          echo "<span class=\"sysnotes\">You must log in to view previous recommendations!</span> <br />";
                        }
                      ?>
                    </td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                </table></td></tr>
            <tr><td><table width=900" border="0" cellpadding="0" cellspacing="0">
                <tr align="center"><img src="footer.jpg"/></tr>
            </table></td></tr>
        </table>
    </SPAN>    
</body>