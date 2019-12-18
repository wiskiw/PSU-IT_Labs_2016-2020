@ECHO off	
choice /N /C:12 /M "1 - Task1, 2 - Task2"
if errorlevel 2 goto task2
if errorlevel 1 goto task1

:task2
./task2 E:\Programming\University\TRIP\lab1 E:\Programming\University\TRIP\ task1.bat 

:task1
./task1
