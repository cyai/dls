#!/bin/bash

g++ -std=c++11 -o output_file dls.cpp

if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    ./output_file
else
    echo "Compilation failed. Please check your code."
fi