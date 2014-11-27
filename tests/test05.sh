#!/bin/bash

[ -z $TESTDIR ] && echo "Need to set TESTDIR variable" && exit 1
# CALCCMD = Es el nombre de la variable definida para ejecutar el comando
CALCCMD=${CALCCMD:=./calc}

# echo "Cmd to execute: $CALCCMD for test 05"

cp $TESTDIR/stmts03.calc .
$CALCCMD -v a=10 -v b=20 -v c=30 -v d=1 -v e=9 stmts03.calc > test05.out

if [ -e test05.out ]
then

    diff test05.out $TESTDIR/test05.out

    if [ $? -eq 0 ]
    then
        echo "test 05 has passed"
    else
        echo "test 05 has failed"
    fi

    rm -f test05.out
else
   echo "test 05 has failed"
fi

rm -f stmts03.calc
