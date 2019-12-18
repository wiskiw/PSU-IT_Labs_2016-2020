@ECHO off

:Yes

Choice /C:yn /M "Once again?"
:: /M - message
:: /C - Specifies the list of choices to be created. Valid choices include a-z, A-Z, 0-9, and extended ASCII characters (128-254). The default list is "YN."

If Errorlevel 2 Goto No
If Errorlevel 1 Goto Yes
:No

::If Errorlevel 1 Goto Yes


