#!/bin/bash

[ -z $TESTDIR ] && echo "Need to set TESTDIR variable" && exit 1
# CALCCMD = Es el nombre de la variable definida para ejecutar el comando
CALCCMD=${CALCCMD:=./calc}

# echo "Cmd to execute: $CALCCMD for test 02"

cp $TESTDIR/stmts02.calc .
$CALCCMD < stmts02.calc > test02.out
diff test02.out $TESTDIR/test02.out

if [ -e test02.out ]
then
    diff test02.out $TESTDIR/test02.out

    if [ $? -eq 0 ]
    then
        echo "test 02 has passed"
    else
        echo "test 02 has not passed"
    fi

    rm -f test02.out
fi

rm -f stmts02.calc
