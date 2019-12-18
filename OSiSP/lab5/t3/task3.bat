:: Копирование группы файлов удовлетворяющих маске из одного каталога в несколько других каталогов. 
:: Маска и каталоги передаются как параметры пакетного файла.

@echo off

if exist %2 pushd %2     


:start

:: /I           If destination does not exist and copying more than one file, assumes that destination must be a directory.
xcopy %1 %3 /i



shift /3
if not '%3' == '' goto :start



popd

:: task3.bat *.txt test E:\UNI\LVL2\PART2\OSiSP\lab5\t3\test2\ E:\UNI\LVL2\PART2\OSiSP\lab5\t3\test3\