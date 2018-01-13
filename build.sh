#!/bin/bash

# It builds project

if [ ! -d "$DIRECTORY" ]; then
  mkdir build
fi
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../
make
make install
