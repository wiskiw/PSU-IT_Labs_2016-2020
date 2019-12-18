@ECHO off
choice /N /C:12 /M "1- time, 2 -  date" 
if ERRORLEVEL 2 date /t
if ERRORLEVEL 1 time /t
