set terminal png
set output 'find.png'

set logscale x
set xl "SIZE"
set yl "Time (sec)"
 set title "Time for 10^5 lookups"
set key left
set grid
plot 'output.dat' u 1:7 w lp ls 3 title "map",\
  'output.dat' u 1:5 w lp ls 4 title "unbalanced tree",\
  'output.dat' u 1:6 w lp ls 5 title "balanced tree"
