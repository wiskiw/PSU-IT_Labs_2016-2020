#!/bin/bash
# file path - $1
# file name mask - $2
# destination 1 - $3
# destination 2 - $4

find $1 -name *$2 -print0|xargs --null cp --parents -t $3
find $1 -name *$2 -print0|xargs --null cp --parents -t $4  