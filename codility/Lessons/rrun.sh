#!/bin/bash

# Program name
PROG=""

if [ $# -eq 0 ]
then
  PROG="rrrMain"
else
  PROG="${1}"
fi

# Name for driver function (if it exists)
FUNC="${PROG}_fun"

if [ -e "Makefile" ]
then
 make clean && ./genmake.sh && make ${PROG}
else
 ./genmake.sh && make ${PROG}
fi

# if the driver function exists, it would be in here.
source drivers.sh

if [ "$(type -t ${FUNC})" = "function" ]
then
  # We run the function
#  make ${PROG} && \
  ${FUNC}
else
  # There is no function for this program, so we run the program
  # directly.
#  make ${PROG} && \
  ./${PROG}
fi

