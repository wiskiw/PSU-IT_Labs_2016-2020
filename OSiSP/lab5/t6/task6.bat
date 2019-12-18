@echo off

if exist %1 pushd %1

for %%i in (*.bat) do start %%i

popd

:: task6.bat test
