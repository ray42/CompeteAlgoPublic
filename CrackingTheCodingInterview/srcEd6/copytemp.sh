#!/bin/bash

filename="$1"
replaceString="TTT"
testfile="${filename/\.template/$replaceString}"
cp ${filename} ${testfile}
