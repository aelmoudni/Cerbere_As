#!/usr/bin/env gnuplot


set datafile commentschars "#"
set datafile separator ' '
set terminal pngcairo size 800,600
set output "frame_50.png"
set title "frame 50"
plot "out_data/out_00050" using 3:4 notitle
#pause -1 "hit return"


