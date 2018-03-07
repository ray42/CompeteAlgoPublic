#!/bin/bash

# Program name
PROG="$1"

# Name for driver function (if it exists)
FUNC="${PROG}_fun"


# if the driver function exists, it would be in here.
source drivers.sh

funruns(){
if [ "$(type -t ${FUNC})" = "function" ]
then
  # We run the function
#  make ${PROG} && \
  ${FUNC}
else
  # No function for this program, so we run the program directly.
#  make ${PROG} && \
  ./${PROG}
fi
}

#make clean && ./genmake.sh && make ${PROG} && ./${PROG}
make clean && ./genmake.sh && make ${PROG} && funruns

