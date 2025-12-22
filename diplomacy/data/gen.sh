#!/usr/bin/env bash

. ../../testdata_tools/gen.sh


use_solution full_solution.cpp

compile hit_2_components.cpp opt
compile large_changes.cpp opt
compile gen_simple_line.cpp opt
compile add_remove.cpp opt
compile star.cpp opt
compile gen_simple_random.cpp opt

samplegroup
sample 1
sample 2

group g1expn 9
limits maxn=10 maxq=20
include_group sample
tc g1-1 gen_simple_random	6 10 3 3
tc g1-2 gen_simple_random	10 20 5 5
tc g1-3 gen_simple_random	10 20 7 3
tc g1-4 gen_simple_random	10 19 5 5
tc g1-5 gen_simple_random	10 18 5 10
tc g1-6 gen_simple_random	10 20 6 6
tc g1-7 hit_2_components    10 20
tc g1-8 hit_2_components    8 20
tc g1-9 large_changes       10 20
tc g1-10 large_changes       9 20
tc g1-11 add_remove 10 20 4 1 0
tc g1-12 add_remove 10 20 4 1 1
tc g1-13 add_remove 10 20 4 0 0
tc g1-14 add_remove 10 20 4 0 1
tc g1-15 add_remove 10 20 4 -1 0
tc g1-16 add_remove 10 20 4 -1 1
tc g1-17 star 10 20 4 1
tc g1-18 star 10 20 4 0
tc g1-19 star 10 20 4 -1

group g2nq 10
limits maxn=2000 maxq=4000
include_group g1expn
tc g2-1 gen_simple_random	2000 4000 1600 200
tc g2-2 gen_simple_random	2000 3999 1200 1000
tc g2-3 gen_simple_random	2000 3998 1300 600
tc g2-4 gen_simple_random	1999 4000 500 2000
tc g2-5 gen_simple_random	30 4000 500 2000
tc g2-6 gen_simple_random	2000 30 10 10
tc g2-7 hit_2_components    2000 4000
tc g2-8 large_changes       2000 4000
tc g2-9 add_remove 2000 4000 500 1 0
tc g2-10 add_remove 2000 4000 500 1 1
tc g2-11 add_remove 2000 4000 500 0 0
tc g2-12 add_remove 2000 4000 500 0 1
tc g2-13 add_remove 2000 4000 500 -1 0
tc g2-14 add_remove 2000 4000 500 -1 1
tc g2-15 star 2000 4000 500 1
tc g2-16 star 2000 4000 500 0
tc g2-17 star 2000 4000 500 -1

group g3low_d 6
limits maxd=10
include_group sample
tc g3-1 gen_simple_random	100000 500000 160000 10
tc g3-2 gen_simple_random	100000 500000 180000 10
tc g3-3 gen_simple_random	100000 500000 100000 9
tc g3-4 gen_simple_random	50000 500000 20000 10
tc g3-5 gen_simple_random	100000 500000 5000 10
tc g3-6 gen_simple_random	10 500000 2500 10
tc g3-7 gen_simple_random	100000 30 10 10
tc g3-8 add_remove 100000 200000 10 1 0
tc g3-9 add_remove 100000 200000 10 1 1
tc g3-10 add_remove 100000 200000 10 0 0
tc g3-11 add_remove 100000 200000 10 0 1
tc g3-12 add_remove 100000 200000 10 -1 0
tc g3-13 add_remove 100000 200000 10 -1 1
tc g3-14 star 100000 200000 10 -1
tc g3-15 star 100000 200000 10 0
tc g3-16 star 100000 200000 10 1

group g4line 17
limits line=1
tc g4-1 add_remove 50000 100000 10000 1 1
tc g4-2 add_remove 50000 100000 10000 -1 1
tc g4-3 gen_simple_line	100000 500000 100000 60000
tc g4-4 gen_simple_line	100000 500000 80000 30000
tc g4-5 gen_simple_line	100000 500000 70000 50000
tc g4-6 gen_simple_line	100000 500000 80000 25000
tc g4-7 gen_simple_line	100000 500000 100000 5000
tc g4-8 gen_simple_line	30 500000 200000 5000
tc g4-9 gen_simple_line	100000 30 10 10
tc g4-10 add_remove 100000 200000 10000 1 1
tc g4-11 add_remove 100000 200000 10000 0 1
tc g4-12 add_remove 100000 200000 10000 -1 1

group g5increasing 14
limits increasing_p=1
tc g5-1 add_remove 50000 100000 10000 1 1
tc g5-2 gen_simple_random	100000 500000 200000 80000 1
tc g5-3 gen_simple_random	100000 500000 180000 60000 1
tc g5-4 gen_simple_random	100000 500000 170000 70000 1
tc g5-5 gen_simple_random	99900 500000 125000 25000 1
tc g5-6 gen_simple_random	30 500000 125000 25000 1
tc g5-7 gen_simple_random	100000 30 10 10 1
tc g5-8 add_remove 100000 200000 40000 1 0
tc g5-9 star 100000 200000 50000 1

group g6decreasing 26
limits decreasing_p=1
tc g6-1 add_remove 50000 100000 10000 -1 1
tc g6-2 gen_simple_random	100000 500000 250000 80000 -1
tc g6-3 gen_simple_random	100000 500000 245000 85000 -1
tc g6-4 gen_simple_random	100000 500000 185000 55000 -1
tc g6-5 gen_simple_random	99900 100000 25000 5000 -1
tc g6-6 gen_simple_random	30 500000 25000 5000 -1
tc g6-7 gen_simple_random	100000 30 10 10 -1
tc g6-8 add_remove 100000 200000 30000 -1 0
tc g6-9 star 100000 200000 50000 -1

group g7full 18
include_group g2nq
include_group g3low_d
include_group g4line
include_group g5increasing
include_group g6decreasing
tc g7-1 add_remove 50000 100000 10000 1 1
tc g7-2 add_remove 50000 100000 10000 -1 1
tc g7-3 gen_simple_random	100000 500000 250000 40000
tc g7-4 gen_simple_random	100000 500000 180000 50000
tc g7-5 gen_simple_random	100000 500000 40000 70000
tc g7-6 gen_simple_random	99900 100000 25000 5000
tc g7-7 hit_2_components    30000 500000
tc g7-8 large_changes       30000 500000
tc g7-9 hit_2_components    40000 500000
tc g7-10 large_changes       40000 500000
tc g7-11 hit_2_components    50000 500000
tc g7-12 large_changes       50000 500000
tc g7-13 add_remove 100000 200000 10 0 0
tc g7-14 star 100000 200000 50000 0

