set terminal png
set output 'find.png'

set xl "SIZE"
set yl "Time (sec)"
 set title "10^7 Lookup in BST"
set key left
set grid
plot 'find1.dat' u 1:2 w lp ls 1 title " find1",\
  'find2.dat' u 1:2 w lp ls 2 title " find2",\
