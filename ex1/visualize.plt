# Visualize Lagrange polynomials by D.A.

load 'parula.pal'

reset

# png
set terminal png size 800,600 enhanced font 'Verdana,16'

# define axis
# remove border on top and right and set color to gray
set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror
# define grid
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12

set key bottom right

set xlabel 'X'
set ylabel 'Y'
set xrange [-1:10]
set yrange [-2:4.5]
set key box opaque

set output 'data.png'
plot 'data_line.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5

set output 'bases.png'
plot 'lks.txt' u 1:2  w l ls 1  lw 2 t "", \
	 'lks.txt' u 1:3  w l ls 3  lw 2 t "", \
	 'lks.txt' u 1:4  w l ls 4  lw 2 t "", \
	 'lks.txt' u 1:5  w l ls 5  lw 2 t "", \
	 'lks.txt' u 1:6  w l ls 6  lw 2 t "", \
	 'lks.txt' u 1:7  w l ls 7  lw 2 t "", \
	 'lks.txt' u 1:8  w l ls 8  lw 2 t "", \
	 'lks.txt' u 1:9  w l ls 9 lw 2 t "", \
	 'lks.txt' u 1:10 w l ls 10 lw 2 t "", \
	 'lks.txt' u 1:11 w l ls 11 lw 2 t "", \
	 'data_line.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5
	 
set output 'lagrange.png'
plot 'lagrange.txt'  u 1:2  w l ls 1  lw 2 t "", \
	 'data_line.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5
	 
set output 'lagrange_noise.png'
plot 'lagrange_noise.txt'  u 1:2  w l ls 1  lw 2 t "", \
	 'data_noise.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5
	 
set output 'lagrange_out.png'
plot 'lagrange_out.txt'  u 1:2  w l ls 1  lw 2 t "", \
	 'data_out.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5


