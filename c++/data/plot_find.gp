set terminal png
set output 'find-O3.png'

set logscale x
set xl "SIZE"
set yl "Time (sec)"
 set title "10^5 Lookup in BST"
set key left
set grid
plot 'find1-O3' u 1:2 w lp ls 1 title " find1",\
  'find1-O3' u 1:3 w lp ls 2 title " find2",\
