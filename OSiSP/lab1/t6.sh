#!/bin/bash
# chmod u+x task6.sh
# ./t6.sh ./

find "$1" -type f -executable ! -name "t6.sh" -exec {} \;