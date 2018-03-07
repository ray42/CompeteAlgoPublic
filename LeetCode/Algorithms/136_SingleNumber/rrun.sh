#!/bin/bash

# Program name
PROG=""

if [ $# -eq 0 ]
then
  PROG="rrrMain"
else
  PROG="${1}"
fi

./../rrun.sh ${PROG}
