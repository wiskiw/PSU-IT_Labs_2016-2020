chcp 1251
@echo off
cls
setlocal ENABLEDELAYEDEXPANSION

if '%1'=='' (
    echo Параметры отсутствуют
    goto :end
) else (
    pushd %1
)


set /a count2=0
for %%i in ("*") do (
    set name=%%i
    set /a count=0
    
    for /L  %%j in (0,1,255) do (
        set "lit=!name:~%%j,1!"

        if "!lit!"=="." set /a count=count+1
        if "!lit!"=="," set /a count=count+1
     	if "!lit!"=="\!" set /a count=count+1
      	if "!lit!"=="?" set /a count=count+1
     	if "!lit!"==";" set /a count=count+1
     	if "!lit!"==":" set /a count=count+1
     	if "!lit!"=="-" set /a count=count+1
      	if "!lit!"=="'" set /a count=count+1
     	if "!lit!"=="(" set /a count=count+1
        if "!lit!"==")" set /a count=count+1
    )

    if !count! GTR 3 (
        echo "%%i"
    rem  move "%%i" "%2"
        set /a count2=count2+1
    )

)
rem echo !count2!
if '!count2!'=='0' (
    echo Файлы не были найдены
	
) 