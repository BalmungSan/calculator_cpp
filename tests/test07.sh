#!/bin/bash

[ -z $TESTDIR ] && echo "Need to set TESTDIR variable" && exit 1
# CALCCMD = Es el nombre de la variable definida para ejecutar el comando
CALCCMD=${CALCCMD:=./calc}

# echo "Cmd to execute: $CALCCMD for test 07"

cp $TESTDIR/stmts03.calc .
export CALCVAR_a=1
export CALCVAR_b=2
export CALCVAR_c=3
export CALCVAR_d=10
export CALCVAR_e=90
$CALCCMD -c stmts03.calc

if [ -e stmts03.ewe ]
then

    ewe stmts03.ewe > test07.out
    diff test07.out $TESTDIR/test07.out

    if [ $? -eq 0 ]
    then
        echo "test 07 has passed"
    else
        echo "test 07 has failed"
    fi

    rm -f test07.out stmts03.calc stmts03.ewe
else
   echo "test 07 has failed"
fi
