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

rrr5DiagonalDifference_fun()
{
read -r -d '' VARIABLE << EOM
3
11 2 4
4 5 6
10 8 -12
EOM

echo "Running ${PROG}"
printf "\n"
echo -e "${VARIABLE}" | ./${PROG} foo bar
printf "\n"
echo "End of ${PROG}"
}

rrr6PlusMinus_fun()
{
read -r -d '' VARIABLE << EOM
6
-4 3 -9 0 4 1
EOM

echo "Running ${PROG}"
printf "\n"
echo -e "${VARIABLE}" | ./${PROG} foo bar
printf "\n"
echo "End of ${PROG}"
}

rrr7Staircase_fun()
{
read -r -d '' VARIABLE << EOM
5
EOM

echo "Running ${PROG}"
printf "\n"
echo -e "${VARIABLE}" | ./${PROG} foo bar
printf "\n"
echo "End of ${PROG}"
}

rrr8MiniMaxSum_fun()
{
read -r -d '' VARIABLE << EOM
1 2 3 4 5
EOM

echo "Running ${PROG}"
printf "\n"
echo -e "${VARIABLE}" | ./${PROG} foo bar
printf "\n"
echo "End of ${PROG}"
}

rrr9BirthdayCakeCandles_fun()
{
read -r -d '' VARIABLE << EOM
4
3 2 1 3
EOM

echo "Running ${PROG}"
printf "\n"
echo -e "${VARIABLE}" | ./${PROG} foo bar
printf "\n"
echo "End of ${PROG}"
}

rrr10TimeConversion_fun()
{
read -r -d '' VARIABLE << EOM
07:05:45PM
EOM

echo "Running ${PROG}"
printf "\n"
echo -e "${VARIABLE}" | ./${PROG} foo bar
printf "\n"
echo "End of ${PROG}"
}








