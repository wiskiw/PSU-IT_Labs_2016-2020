rem ./task2 E:\Programming\University\TRIP\lab1 E:\Programming\University\TRIP\ task1.bat
@ECHO off
set path1=%1
set path2=%2
set filename=%3
echo you enter path to file %path1%
echo you enter name of file %filename%
cd %path1%
copy %filename% %path2%
cd %path2%
dir %path2%
echo "Done!"