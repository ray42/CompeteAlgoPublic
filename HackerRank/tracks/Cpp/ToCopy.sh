#!/bin/bash

FromDir="Warmup"
DIR="${1}"

cp ./${FromDir}/drivers.sh ./${DIR}/
cp ./${FromDir}/GCCFLAGS ./${DIR}/
cp ./${FromDir}/genmake.sh ./${DIR}/
cp ./${FromDir}/rrun.sh ./${DIR}/



