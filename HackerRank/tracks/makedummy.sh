#!/bin/bash

CURRDIR=`pwd`

for f in ${CURRDIR}/*;
  do 
     [ -d $f ] && cd "$f" && touch .gitkeep
  done;



