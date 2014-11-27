#!/bin/bash

[ -z $TESTDIR ] && echo "Need to set TESTDIR variable" && exit 1
# CALCCMD = Es el nombre de la variable definida para ejecutar el comando
CALCCMD=${CALCCMD:=./calc}

# echo "Cmd to execute: $CALCCMD for test 06"

cp $TESTDIR/stmts03.calc .
$CALCCMD -v a=1 -v b=2 -v c=3 -v d=10 -v e=90 -c stmts03.calc

if [ -e stmts03.ewe ]
then

    ewe stmts03.ewe > test06.out
    diff test06.out $TESTDIR/test06.out

    if [ $? -eq 0 ]
    then
        echo "test 06 has passed"
    else
        echo "test 06 has failed"
    fi

    rm -f test06.out stmts03.calc stmts03.ewe
else
   echo "test 06 has failed"
fi
