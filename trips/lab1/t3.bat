@ECHO off

choice /M "Wanna see hello world from other .bat?"
if errorlevel 2 goto No

./hello.bat

:No
