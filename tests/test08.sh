#!/bin/bash

[ -z $TESTDIR ] && echo "Need to set TESTDIR variable" && exit 1
# CALCCMD = Es el nombre de la variable definida para ejecutar el comando
CALCCMD=${CALCCMD:=./calc}

# echo "Cmd to execute: $CALCCMD for test 08"

cp $TESTDIR/stmts03.calc .
export CALCVAR_a=1
export CALCVAR_b=2
export CALCVAR_c=3
$CALCCMD -v d=10 -v e=90 -c stmts03.calc 

if [ -e stmts03.ewe ]
then

    ewe stmts03.ewe > test08.out
    diff test08.out $TESTDIR/test08.out

    if [ $? -eq 0 ]
    then
        echo "test 08 has passed"
    else
        echo "test 08 has failed"
    fi

    rm -f test08.out stmts03.calc stmts03.ewe
else
   echo "test 08 has failed"
fi
