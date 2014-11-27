#!/bin/bash

[ -z $TESTDIR ] && echo "Need to set TESTDIR variable" && exit 1
# CALCCMD = Es el nombre de la variable definida para ejecutar el comando
CALCCMD=${CALCCMD:=./calc}

# echo "Cmd to execute: $CALCCMD for test 03"

$CALCCMD -c < $TESTDIR/stmts02.calc > /dev/null

if [ -e a.ewe ]
then
    ewe a.ewe > test03.out

    diff test03.out $TESTDIR/test03.out

    if [ $? -eq 0 ]
    then
        echo "test 03 has passed"
    else
        echo "test 03 has failed"
    fi

    rm -f test03.out a.ewe
else
   echo "test 03 has failed"
fi
