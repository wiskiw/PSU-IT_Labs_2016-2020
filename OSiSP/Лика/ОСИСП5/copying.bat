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
		set mask="%2"
		if "%3" == "" (
			echo ����������� ������ ��������
		) else (
			:loop
  			if "%3" == "" goto finish
  			copy %mask% %3
  			shift
  			goto loop
		)
	)
	:finish
	popd
)
