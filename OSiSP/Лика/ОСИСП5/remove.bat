chcp 1251
@echo off

cls


if "%1" == "" (
	echo ����������� ���������
	goto finish
) else (
	if exist "%1" (
	pushd %1
)	else (
	echo ������� %1 �� ����������
	echo ����� ����� ����������� � ������� �������� "%CD%"
)
	if "%2" == "" (
		echo ����������� ������ ��������
	) else (
		:loop
  		if "%2" == "" goto finish
		echo.
		echo �� ����� %2:
		echo.
  		del /s %2
  		shift
  		goto loop
	)
	:finish
	popd
)
