@echo off

set PATH=C:\Program Files (x86)\PuTTY\;%PATH% 
set linscr=C:\Users\Gary\Documents\school\projects\graduate\cs6387-advanced-operating-systems\program1\linuxscript.sh
::psftp -pw Jetpack42! gxs112030@cs1.utdallas.edu -b psftpscr
::@echo "Script upload complete."
::plink -pw Jetpack42! gxs112030@cs1.utdallas.edu cs6378/hw1/program1/linuxscript.sh
::plink -pw Jetpack42! gxs112030@cs1.utdallas.edu -m %linscr%

START /B putty -pw Jetpack42! -m "C:\Users\Gary\Documents\school\projects\graduate\cs6387-advanced-operating-systems\p1\node_1.sh" gxs112030@cs2.utdallas.edu
::START /B putty -pw Jetpack42! gxs112030@cs1.utdallas.edu
::START /B putty -pw Jetpack42! gxs112030@cs1.utdallas.edu
::START /B putty -pw Jetpack42! gxs112030@cs1.utdallas.edu


@echo off
@pause
@echo "End of script"