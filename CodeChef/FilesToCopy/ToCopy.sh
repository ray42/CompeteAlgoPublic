#!/bin/bash
# Usage: Go into the directory you want to copy the files to.
# run: ./../../FilesToCopy/ToCopy.sh

FromDir="/home/ray/learning/CodeChef/FilesToCopy"
DIR=`pwd`
cp ${FromDir}/drivers.sh ${DIR}/
cp ${FromDir}/GCCFLAGS ${DIR}/
cp ${FromDir}/genmake.sh ${DIR}/
cp ${FromDir}/run.sh ${DIR}/
