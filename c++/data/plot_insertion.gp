set terminal png
set output 'insertion.png'

set logscale x
set logscale y
set xl "SIZE"
set yl "Time (sec)"
 set title "Insertion and balancing"
set key left
set grid
plot 'output.dat' u 1:2 w lp ls 3 title "map insert",\
  'output.dat' u 1:3 w lp ls 4 title "tree insert",\
  'output.dat' u 1:4 w lp ls 5 title "tree balance"
