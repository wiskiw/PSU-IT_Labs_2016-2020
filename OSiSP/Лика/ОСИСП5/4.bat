@echo off
chcp 1251

:start
cls

echo Выберите действие:
echo.
echo 1. Задание №1
echo 2. Задание №2
echo 3. Задание №3
echo 4. Задание №4
echo 5. Выход
echo.
CHOICE /N /C:12345
if ERRORLEVEL 5 goto exit
if ERRORLEVEL 4 goto option4
if ERRORLEVEL 3 goto option3
if ERRORLEVEL 2 goto option2
if ERRORLEVEL 1 goto option1

:option4
CALL ".\5.bat"
goto start

:option3
CALL ".\4.bat"
goto start

:option2
CALL ".\3.bat"
goto start

:option1
CALL ".\2.bat"
goto start

:exit