#!/usr/bin/env bash

. ../../testdata_tools/gen.sh


use_solution garbage-full_cc.cpp

compile generator.cpp opt
samplegroup
sample 1

group g1cubic 10
limits maxn=400
include_group sample
tc g1-1 generator   GZFCiftUVz  1       xy_uniform  1           w_constant  10          1           1
tc g1-2 generator   DEsAxOJTim  10      xy_uniform  10          w_uniform   10
tc g1-3 generator   SwzlwoMZta  391     xy_uniform  1000000000  w_constant  1
tc g1-4 generator   NispNtPfvj  400     xy_uniform  1000000000  w_uniform   1000000000
tc g1-5 generator   xrHwnDPxym  400     xy_uniform  1000000000  w_uniform   1000000000
tc g1-6 generator   hVwrYJTXSP  400     xy_uniform  1000000000  w_uniform   1000000000
tc g1-7 generator   BkGArHOReu  400     xy_uniform  1000000000  w_extremes  1000000000
tc g1-8 generator   JLlPaXMQtO  400     xy_hotspots 1000000000  3       10       w_uniform  1000000000
tc g1-9 generator   PazlhQqwfh  400     xy_hotspots 1000000000  80      1000000  w_uniform  1000000000
tc g1-10 generator   BLHPsNbVwX  400     xy_hotspots 1000000000  80      1000000  w_extremes 1000000000
tc g1-11 generator   KjkQYMJWAl  400     xy_anti_random  1000000000  2       1000000     1000000     1   w_constant  1000000000   1000000     1000000
tc g1-12 generator   ZGQgOAnzBN  400     xy_anti_random  1000000000  15      1000000     1000000     1   w_constant  1000000000   1000000     1000000
tc g1-13 generator   cdatxcCrmn  400     xy_mix      1000000000  100         100         10      200000000   200000000   0   w_uniform  1000000000   200000000   200000000
tc g1-14 generator   rUtqIMHYvS  400     xy_mix      1000000000  100         100         10      200000000   200000000   0   w_extremes 1000000000   200000000   200000000

group g2small_sea 12
limits maxside=2000 maxcoord=2000
include_group sample
tc g2-1 generator   HVDYulnXLN  1       xy_uniform  1           w_constant  10          1           1
tc g2-2 generator   PqPFDetCEv  10      xy_uniform  10          w_uniform   10
tc g2-3 generator   eSmLDYqANZ  10000   xy_uniform  2000        w_constant  1
tc g2-4 generator   BuSOJZGGVA  99991   xy_uniform  2000        w_uniform   1000000000
tc g2-5 generator   IdiAmPlmUR  100000  xy_uniform  2000        w_uniform   1000000000
tc g2-6 generator   TNpIkWjyRz  100000  xy_uniform  2000        w_extremes  1000000000
tc g2-7 generator   fhyeZwTxEP  100000  xy_hotspots 2000        3       10       w_uniform  1000000000
tc g2-8 generator   zoIRmRxbyP  100000  xy_hotspots 2000        80      20       w_extremes 1000000000
tc g2-9 generator   YfIrcIyHSs  100000  xy_anti_random  2000        5       100         100         1   w_constant  1000000000   100         100
tc g2-10 generator   xxYoOxUcHw  100000  xy_anti_random  2000        3       200         100         1   w_constant  1000000000   200         100
tc g2-11 generator   rIDvHrpnef  100000  xy_mix      2000        1000        20          10      600         1           0   w_uniform  1000000000   600         1
tc g2-12 generator   mUGuhGygBN  100000  xy_mix      2000        1000        30          10      1200        1500        0   w_extremes 1000000000   1500        1200

group g3quadratic 15
include_group sample cubic
tc g3-1 generator   dPnEKsLUMQ  1991    xy_uniform  1000000000  w_uniform   1000000000
tc g3-2 generator   VRJAWbBpDY  2000    xy_uniform  1000000000  w_uniform   1000000000
tc g3-3 generator   gMnaJeuHtg  2000    xy_uniform  1000000000  w_uniform   1000000000
tc g3-4 generator   RJNLUevDEj  2000    xy_uniform  1000000000  w_extremes  1000000000
tc g3-5 generator   QEPApZhoBk  2000    xy_hotspots 1000000000  3       10       w_uniform  1000000000
tc g3-6 generator   EHJYgVKBeC  2000    xy_hotspots 1000000000  80      1000000  w_uniform  1000000000
tc g3-7 generator   IPGgZlZYbv  2000    xy_hotspots 1000000000  80      1000000  w_extremes 1000000000
tc g3-8 generator   qsiyLRSlUF  2000    xy_anti_random  1000000000  4       1000000     1000000     1   w_constant  1000000000   1000000     1000000
tc g3-9 generator   mjiHvIeghf  2000    xy_anti_random  1000000000  10      1000000     1000000     1   w_constant  1000000000   1000000     1000000
tc g3-10 generator   WRbCPwRCjd  2000    xy_mix      1000000000  100         100         10      200000000   200000000   0   w_uniform  1000000000   200000000   200000000
tc g3-11 generator   tgYrqfuQGo  2000    xy_mix      1000000000  100         100         10      200000000   200000000   0   w_extremes 1000000000   200000000   200000000

group g4single_dimension 22
tc g4-1 generator   jAGNHmcapl  1       xy_uniform  1           w_constant  10          1           1000000000
tc g4-2 generator   EcVNOqcPpb  10      xy_uniform  10          w_uniform   10          1000000000
tc g4-3 generator   rFeaSpOYiC  10000   xy_uniform  1000000000  w_constant  1           1000000000
tc g4-4 generator   qZweBYNeJy  99991   xy_uniform  1000000000  w_uniform   1000000000  1000000000
tc g4-5 generator   RvdNxIxDzJ  100000  xy_uniform  1000000000  w_uniform   1000000000  1000000000
tc g4-6 generator   EZQmfsxsgm  100000  xy_uniform  1000000000  w_extremes  1000000000  1000000000
tc g4-7 generator   lAcsWBnDcU  100000  xy_hotspots 1000000000  3       10       w_uniform  1000000000  1000000000
tc g4-8 generator   vQTAODBvdF  100000  xy_hotspots 1000000000  80      1000000  w_extremes 1000000000  1000000000
tc g4-9 generator   UmBPYiMoBB  100000  xy_anti_random  1000000000  2       100000      1000000000  1   w_constant  1000000000   100000      1000000000
tc g4-10 generator   tuoDLGbGDH  100000  xy_anti_random  1000000000  15      100000      1000000000  1   w_constant  1000000000   100000      1000000000
tc g4-11 generator   MIdYuVRBGo  100000  xy_mix      1000000000  100         100         10      20000000    200000000   0   w_uniform  1000000000   200000000   1000000000

group g5limited_sea 23
include_group sample small_sea
tc g5-1 generator   flrmFHzbYZ  99991   xy_uniform  100000      w_uniform   1000000000
tc g5-2 generator   EsMYlUcrlK  100000  xy_uniform  100000      w_uniform   1000000000
tc g5-3 generator   XjBQUpeygo  100000  xy_uniform  100000      w_uniform   1000000000
tc g5-4 generator   MXuAgEFbAj  100000  xy_uniform  100000      w_extremes  1000000000
tc g5-5 generator   VeOHnFIStZ  100000  xy_hotspots 100000      3       10      w_uniform  1000000000
tc g5-6 generator   vZJFzCXerk  100000  xy_hotspots 100000      80      500     w_extremes 1000000000
tc g5-7 generator   OuuCNaYWNc  100000  xy_anti_random  100000      2       10000       10000       1   w_constant  1000000000   10000       10000
tc g5-8 generator   CPbfjsstEh  100000  xy_anti_random  100000      3       10000       10000       1   w_constant  1000000000   10000       10000
tc g5-9 generator   POBQqzPdDc  100000  xy_anti_random  100000      5       10000       10000       1   w_constant  1000000000   10000       10000
tc g5-10 generator   MncJJgqRTX  100000  xy_anti_random  100000      5       100         20000       1   w_constant  1000000000   100         20000
tc g5-11 generator   PerIQqAExy  100000  xy_anti_random  100000      15      10000       10000       1   w_constant  123456789    10000       10000
tc g5-12 generator   jyJMOgssdl  100000  xy_mix      100000      100         100         10      20000   20000   0   w_uniform  1000000000   20000   20000

group g6full 18
include_group sample cubic small_sea quadratic single_dimension limited_sea
tc g6-1 generator   pjQeiOUSZy  99991   xy_uniform  1000000000  w_uniform   1000000000
tc g6-2 generator   cYXojcFJxQ  100000  xy_uniform  1000000000  w_uniform   1000000000
tc g6-3 generator   hJhiBSvVnR  100000  xy_uniform  1000000000  w_uniform   1000000000  650000000   400000000
tc g6-4 generator   MxDpUyCArM  100000  xy_uniform  1000000000  w_uniform   1000000000  30000   30000
tc g6-5 generator   fjWIQrfeTC  100000  xy_uniform  1000000000  w_extremes  1000000000
tc g6-6 generator   JvuNmsznkQ  100000  xy_hotspots 1000000000  3       10      w_uniform  1000000000
tc g6-7 generator   zcfJzUaZCI  100000  xy_hotspots 1000000000  80      500     w_extremes 1000000000
tc g6-8 generator   DDqAmwgQkT  100000  xy_anti_random  1000000000  3       100000000   100000000   1   w_constant  1000000000   100000000   100000000
tc g6-9 generator   IQrsFzqYjZ  100000  xy_anti_random  1000000000  5       100         20000       0   w_constant  1000000000   100         20000
tc g6-10 generator   gKhHoZjDst  100000  xy_anti_random  1000000000  15      1000000     1000000     1   w_constant  123456789    1000000     1000000
tc g6-11 generator   UZSvrfxbGh  100000  xy_anti_random  1000000000  5       10000000    99999999    1   w_constant  1            10000000    10000000
tc g6-12 generator   xIYgJnjear  100000  xy_anti_random  1000000000  200     15          100000      0   w_constant  111111111    15          100000
tc g6-13 generator   ndOBpOZIoW  100000  xy_mix      1000000000  100         100         10      20000   20000   0   w_uniform  1000000000   20000   20000

