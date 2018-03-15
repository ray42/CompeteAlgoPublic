#!/bin/bash

for d in */ ; do
  cd ${d}
  if [ -e "Makefile" ]
  then
    make clean
    rm Makefile
  fi
  cd ..
done

