#!/bin/bash

problem=diplomacy

g++ -std=gnu++17 -O2 -pipe -static -s -o $problem $problem.cpp
