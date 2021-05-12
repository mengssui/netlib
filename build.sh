#!/bin/bash
###
 # @Descripttion: 
 # @version: 0.1
 # @Author: Mengbw
 # @Date: 2021-05-12 16:57:02
 # @LastEditors: Mengbw
 # @LastEditTime: 2021-05-12 18:06:21
### 
set -x

SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-./build}
BUILD_TYPE=${BUILD_TYPE:-debug}
INSTALL_DIR=${INSTALL_DIR:-../${BUILD_TYPE}-install}
BUILD_NO_EXAMPLE=${BUILD_NO_EXAMPLE:-0}

mkdir -p $BUILD_DIR \
  && cd $BUILD_DIR  \
  && cmake $SOURCE_DIR  \
  && make $*

