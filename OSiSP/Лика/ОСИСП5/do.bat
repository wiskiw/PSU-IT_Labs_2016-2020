chcp 1251
@echo off
cls

if '%1' == '' (
   echo "Параметры отсутствуют"
   goto :end
)

:begin
if exist %1 (
            pushd %1
) else ( 
        echo Каталог %1 не существует
	echo Поиск будет осуществлен в текущем каталоге "%CD%"
)

for %%i in (*.bat) do start %%i
for %%j in (*.exe) do start %%j
popd

shift 
if '%1' == '' (
     goto :end
) else (
     goto :begin
)

:end
)