set title 'test'
set grid
set xlabel 'n'
set ylabel 'delta'
set format y '%.3e'
set pointsize 1
plot 'test.dat' using 1:2 with points title 'Initial Points'
