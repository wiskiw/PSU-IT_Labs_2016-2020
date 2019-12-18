#!/bin/bash

#./t4.sh ./test1 ./test2

pathLocation=$1
pathDestination=$2

ls $pathLocation/*[0-9]*[0-9]*[0-9]*
mv $pathLocation/*[0-9]*[0-9]*[0-9]* $pathDestination 
