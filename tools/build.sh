#!/bin/bash

# installation
sudo apt-get install libsfml-dev
sudo apt install g++
sudo apt install cmake

# go to the upper dirctory
# if the directory exists, do not create it
# go to it
cd ..
mkdir -p build
cd build

# create and run the makefile
cmake ..
make
