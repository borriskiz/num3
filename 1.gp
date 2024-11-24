set grid
set xlabel 'x'
set ylabel 'y'
set format y '%.3e'
set pointsize 1
plot '1_points_Initial Points.dat' using 1 : 2 with points title 'Initial Points',  '1_function_Gausian.dat' using 1:2 with lines title 'Gausian'