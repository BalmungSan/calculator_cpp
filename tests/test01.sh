#!/usr/bin/bash

[ -z $TESTDIR ] && echo "Need to set TESTDIR variable" && exit 1
# CALCCMD = Es el nombre de la variable definida para ejecutar el comando
CALCCMD=${CALCCMD:=./calc}

echo "Cmd to execute: $CALCCMD for test 01"

cp $TESTDIR/stmts01.calc .
$CALCCMD < stmts01.calc > test01.out

if [ -e test01.out ]
then
    diff test01.out $TESTDIR/test01.out

    if [ $? -eq 0 ]
    then
        echo "test 01 has passed"
    else
        echo "test 01 has failed"
    fi

    rm -f test01.out
else
    echo "test 01 has failed"
fi

rm -f stmts01.calc
