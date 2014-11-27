#!/bin/bash

[ -z $TESTDIR ] && echo "Need to set TESTDIR variable" && exit 1
# CALCCMD = Es el nombre de la variable definida para ejecutar el comando
CALCCMD=${CALCCMD:=./calc}

# echo "Cmd to execute: $CALCCMD for test 04"

cp $TESTDIR/stmts03.calc .
$CALCCMD stmts03.calc > test04.out

if [ -e test04.out ]
then

    diff test04.out $TESTDIR/test04.out

    if [ $? -eq 0 ]
    then
        echo "test 04 has passed"
    else
        echo "test 04 has failed"
    fi

    rm -f test04.out
else

   echo "test 04 has failed"
fi

rm -f stmts03.calc
