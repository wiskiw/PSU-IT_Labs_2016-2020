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
		set mask="%2"
		if "%3" == "" (
			echo Отсутствует третий параметр
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
