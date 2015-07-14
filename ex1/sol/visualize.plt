# Visualize Lagrange polynomials by D.A.T

load 'parula.pal'

reset

# png
set terminal png size 1280,800 enhanced font 'Verdana,16'

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
set xrange [-1:11]
set yrange [-4.5:4.5]
set key box opaque

set output 'init-data.png'
plot 'init-data.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5

set output 'bases.png'
plot 'lk0.txt' u 1:2  w l ls 1  lw 2 t "", \
	 'lk1.txt' u 1:2  w l ls 3  lw 2 t "", \
	 'lk2.txt' u 1:2  w l ls 4  lw 2 t "", \
	 'lk3.txt' u 1:2  w l ls 5  lw 2 t "", \
	 'lk4.txt' u 1:2  w l ls 6  lw 2 t "", \
	 'lk5.txt' u 1:2  w l ls 7  lw 2 t "", \
	 'lk6.txt' u 1:2  w l ls 8  lw 2 t "", \
	 'lk7.txt' u 1:2  w l ls 9  lw 2 t "", \
	 'lk8.txt' u 1:2  w l ls 10 lw 2 t "", \
	 'lk9.txt' u 1:2  w l ls 11 lw 2 t "", \
	 'init-data.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5

set output 'lagrange.png'
plot 'lagr.txt'  u 1:2  w l ls 1  lw 2 t "", \
	 'init-data.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5

set output 'lagrange_noise.png'
plot 'lagr-noise.txt'  u 1:2  w l ls 1  lw 2 t "", \
	 'init-data.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5

set output 'lagrange_outliner.png'
plot 'lagr-outliner.txt'  u 1:2  w l ls 1  lw 2 t "", \
	 'init-data.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5