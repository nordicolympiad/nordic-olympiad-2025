#!/usr/bin/env bash

. ../../testdata_tools/gen.sh


use_solution ../printnothing.cpp

compile generator.cpp opt

samplegroup
limits q=n-1
sample sample-1
sample sample-2

group g1 8
limits special1=1 maxn=1000 q=n-1
tc_manual ../manual_tests/simple-1.in
tc sample-2
tc g1-3 generator subtask1 1 15 Something
tc g1-4 generator subtask1 1 100 Anything
tc g1-5 generator subtask1 1 537 Everything
tc g1-6 generator subtask1 1 999 TheThing
tc g1-7 generator subtask1 1 1000 ManThing

group g2 5
limits special2=1 maxn=1000 q=n-1
include_group g1
tc_manual ../manual_tests/deg0.in
tc_manual ../manual_tests/deg0_2.in
tc_manual ../manual_tests/oob.in
tc g2-4 generator max3 2 121 Hulk
tc g2-5 generator max3 2 987 Hawkeye
tc g2-6 generator subtask2 2 130 CaptainAmerica
tc g2-7 generator subtask2 2 1000 IronMan
tc g2-8 generator subtask2det 2 999 Falcon

group g3 9
limits maxn=300 q=n_squared
tc_manual ../manual_tests/deg0_sub3.in
tc_manual ../manual_tests/oob_2_sub3.in
tc g3-3 generator line 3 25 Donde
tc g3-4 generator line 3 291 esta
tc g3-5 generator random_line 3 31 la
tc g3-6 generator random_line 3 292 biblioteca
tc g3-7 generator max3 3 293 Me
tc g3-8 generator degrees 3 293 llamo
tc g3-9 generator star 3 294 T-bone
tc g3-10 generator general 3 50 la
tc g3-11 generator general 3 150 arana
tc g3-12 generator general 3 300 discoteca

group g4 11
limits maxn=1000 q=45000
tc_manual ../manual_tests/deg0_sub4.in
tc_manual ../manual_tests/oob_2_sub4.in
tc g4-3 generator random_line 4 20 Seed
tc g4-4 generator line 4 991 Tree
tc g4-5 generator random_line 4 1000 Leaf
tc g4-6 generator random_line 4 1000 Leaves
tc g4-7 generator max3 4 993 Root
tc g4-8 generator degreesdet 4 1000 Blossom
tc g4-9 generator degrees 4 1000 Blossom
tc g4-10 generator star 4 994 Fruit
tc g4-11 generator general 4 50 Kernel
tc g4-12 generator general 4 567 Plant
tc g4-13 generator general 4 1000 Flower

group g5 24
limits maxn=1000 q=n-1
include_group sample g1 g2
tc_manual ../manual_tests/oob_2.in
tc g5-2 generator line 5 954 Once
tc g5-3 generator random_line 5 965 Upon
tc g5-4 generator max3 5 976 A
tc g5-5 generator degrees 5 987 Time
tc g5-6 generator star 5 998 In
tc g5-7 generator general 5 45 A
tc g5-8 generator general 5 498 Kingdom
tc g5-9 generator general 5 1000 Far

group g6 43
limits maxn=100000 q=n-1
include_group sample g1 g2 g5
tc g6-1 generator general 6 2000 Asbjoern
tc g6-2 generator general 6 10000 Sebastian
tc g6-3 generator line 6 100000 Elias
tc g6-4 generator random_line 6 100000 Thor
tc g6-5 generator random_line 6 100000 Christian
tc g6-6 generator random_line 6 100000 Maja
tc g6-7 generator max3 6 100000 Markus
tc g6-8 generator max3beg 6 100000 Lind
tc g6-9 generator max3end 6 100000 Maja
tc g6-10 generator max3mid 6 100000 Freja
tc g6-11 generator degrees 6 100000 Anders
tc g6-12 generator degrees 6 100000 William
tc g6-13 generator star 6 100000 David
tc g6-14 generator star_beg 6 100000 Lolck
tc g6-15 generator star_end 6 100000 Vejen
tc g6-16 generator maxor 6 100000 Aabjoern
tc g6-17 generator general 6 100000 Edith
tc g6-18 generator general 6 100000 Bodil
tc g6-19 generator general 6 100000 Nikolaj
