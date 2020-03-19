#!/bin/bash

rm -rf build
git commit -am \"$1\"
git push -u origin master
mkdir build
cd build
cmake ..