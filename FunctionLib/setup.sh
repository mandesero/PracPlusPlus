#!/bin/bash

cd lib
git clone https://github.com/google/googletest.git
cd ..
mkdir build
cd build
cmake ..
make && make test