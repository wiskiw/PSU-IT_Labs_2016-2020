#!/bin/bash

# ./t1.sh ./test1 *.txt
MY_PATH=$1/$2

echo 'path: '$MY_PATH
echo 'result: '

echo | ls $MY_PATH