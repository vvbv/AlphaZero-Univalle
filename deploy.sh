#!/bin/bash
rm ./alpha_zero
clear
g++ --std=c++11 src/*.cpp -I include/ -o alpha_zero
./alpha_zero