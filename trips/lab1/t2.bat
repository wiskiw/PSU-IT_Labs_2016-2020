:: t2 . t1

@ECHO off
set filePath=%1
set fileName=%2

if exist %filePath%/%fileName% (
    echo File %filePath%/%fileName% exists
) else (
    echo File %filePath%/%fileName% doesn't exist
)
