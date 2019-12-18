chcp 1251
@echo off

cls


if "%1" == "" (
	echo Отсутствуют параметры
	goto finish
) else (
	if exist "%1" (
	pushd %1
)	else (
	echo Каталог %1 не существует
	echo Поиск будет осуществлен в текущем каталоге "%CD%"
)
	if "%2" == "" (
		echo Отсутствует второй параметр
	) else (
		:loop
  		if "%2" == "" goto finish
		echo.
		echo По маске %2:
		echo.
  		dir /b /s %2
  		shift
  		goto loop
	)
	:finish
	popd
)
