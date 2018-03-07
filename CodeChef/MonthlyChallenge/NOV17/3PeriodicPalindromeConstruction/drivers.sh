#!/bin/bash

test_fun()
{
read -r -d '' VARIABLE << EOM
qwerty
EOM

echo "Running ${PROG}"
printf "\n"
echo -e "${VARIABLE}" | ./${PROG} foo bar
printf "\n"
echo "End of ${PROG}"
}

rrrmain_fun()
{
read -r -d '' VARIABLE << EOM
5
3 3
4 4
5 5
6 6
7 7
8 8
9 9
10 10
11 11
EOM

echo "Running ${PROG}"
printf "\n"
echo -e "${VARIABLE}" | ./${PROG} foo bar
printf "\n"
echo "End of ${PROG}"
}


#rrrmain_fun()
#{
#read -r -d '' VARIABLE << EOM
#5
#3 1
#2 2
#3 3
#4 4
#6 3
#EOM
#
#echo "Running ${PROG}"
#printf "\n"
#echo -e "${VARIABLE}" | ./${PROG} foo bar
#printf "\n"
#echo "End of ${PROG}"
#}


