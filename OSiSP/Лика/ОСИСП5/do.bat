chcp 1251
@echo off
cls

if '%1' == '' (
   echo "��������� �����������"
   goto :end
)

:begin
if exist %1 (
            pushd %1
) else ( 
        echo ������� %1 �� ����������
	echo ����� ����� ����������� � ������� �������� "%CD%"
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