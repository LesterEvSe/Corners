#!/bin/bash

# install sfml
sudo apt-get install libsfml-dev
sudo apt install g++
sudo apt install cmake

# if the directory exists, do not create it
mkdir -p build
cd build

# create a makefile
cmake ..
make

# run the game
./Corners
