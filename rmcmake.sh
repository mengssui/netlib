#!/bin/bash
###
 # @Descripttion: 
 # @version: 0.1
 # @Author: Mengbw
 # @Date: 2021-05-15 19:08:03
 # @LastEditors: Mengbw
 # @LastEditTime: 2021-05-15 19:08:03
### 

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

if [[ -e "./lib" ]];then
  rm -rf ./lib
  echo "Clear ./lib Cmake Finish!"
else
  echo "No need to clear ./lib"
fi


