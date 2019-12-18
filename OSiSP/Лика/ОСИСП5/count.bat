@echo off
chcp 1251

cls


if "%1" == "1" CALL ".\1.bat" %2 %3 %4
if "%1" == "2" CALL ".\2.bat" %2 %3 %4
if "%1" == "3" CALL ".\3.bat" %2 %3 %4

