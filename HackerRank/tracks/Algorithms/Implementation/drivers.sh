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

rrrGradingStudents_fun()
{
read -r -d '' VARIABLE << EOM
4
73
67
38
33
EOM

echo "Running ${PROG}"
printf "\n"
echo -e "${VARIABLE}" | ./${PROG} foo bar
printf "\n"
echo "End of ${PROG}"
}


rrrAppleAndOrange_fun()
{
read -r -d '' VARIABLE << EOM
7 11
5 15
3 2
-2 2 1
5 -6
EOM

echo "Running ${PROG}"
printf "\n"
echo -e "${VARIABLE}" | ./${PROG} foo bar
printf "\n"
echo "End of ${PROG}"
}






