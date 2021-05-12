#!/bin/bash

#set -x
set -u 

if [[ -e "./bin" ]];then
  rm -rf ./bin
  echo "Clear ./bin Cmake Finish!"
else
  echo "No need to clear ./bin"
fi

if [[ -e "./build" ]];then
  rm -rf ./build
  echo "Clear ./build Cmake Finish!"
else
  echo "No need to clear ./build"
fi
# cd $FULLBIN


