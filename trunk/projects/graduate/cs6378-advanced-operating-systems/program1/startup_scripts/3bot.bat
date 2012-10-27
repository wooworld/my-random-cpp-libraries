@echo off

set PATH=C:\Program Files (x86)\PuTTY\;%PATH% 

::START /B putty -pw Jetpack42! -m "C:\Users\Gary\Documents\school\projects\graduate\cs6387-advanced-operating-systems\p1\node0ssh.sh" gxs112030@cs2.utdallas.edu
::START /B putty -pw Jetpack42! gxs112030@cs2.utdallas.edu

START /B putty -l gxs112030 -pw Jetpack42! -load "cs2.utdallas.edu"
START /B putty -l gxs112030 -pw Jetpack42! -load "cs2.utdallas.edu"
START /B putty -l gxs112030 -pw Jetpack42! -load "cs2.utdallas.edu"
START /B putty -l gxs112030 -pw Jetpack42! -load "cs2.utdallas.edu"

@echo off
@pause
@echo "End of script"