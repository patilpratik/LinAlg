#!/bin/bash

# It builds Unit tests for project
if [ ! -d "build" ]; then
  mkdir build
fi
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../ -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
make
