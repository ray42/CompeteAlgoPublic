#!/bin/bash

# Program name
PROG="$1"

# Name for driver function (if it exists)
FUNC="${PROG}_fun"


#make clean && ./genmake.sh && make ${PROG} && ./${PROG}
make clean && ./genmake.sh && make ${PROG}


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




