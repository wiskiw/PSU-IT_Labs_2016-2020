#!/bin/bash
#   ./t2.sh $HOME/test *.txt

FIND_CMD='find '$1' -name '$2
echo 'files to remove: '
$FIND_CMD 
$FIND_CMD '-delete'