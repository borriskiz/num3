set grid
set xlabel 'x'
set ylabel 'y'
set format y '%.3e'
set pointsize 1
plot '2_points_Initial Points.dat' using 1 : 2 with points title 'Initial Points',  '2_function_LU.dat' using 1:2 with lines title 'LU'