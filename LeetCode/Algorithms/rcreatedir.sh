#!/bin/bash

DIR="$1"

if [ -d "$DIR" ]; then
  echo "directory exists"
else
  mkdir ${DIR}
  cp 1_TwoSum/drivers.sh ./${DIR}/
  cp 1_TwoSum/genmake.sh ./${DIR}/
  cp 1_TwoSum/rrun.sh ./${DIR}/
  cp rrrMain.cpp ./${DIR}/
fi

