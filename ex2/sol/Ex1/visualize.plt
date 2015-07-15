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
set xrange [-1:10]
set yrange [-2:4.5]
set key box opaque

set output 'data.png'
plot 'data-straight.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5

set output 'lsq_straight.png'
plot 'lsq-straight.txt' u 1:2  w l ls 1  lw 2 t "", \
	 'data-straight.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5
	 
set output 'lsq_noise1.png'
plot 'lsq-noise1.txt'  u 1:2  w l ls 1  lw 2 t "", \
	 'data-noise1.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5
	 	 
set output 'lsq_noise2.png'
plot 'lsq-noise2.txt'  u 1:2  w l ls 1  lw 2 t "", \
	 'data-noise2.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5
	 	 
set output 'lsq_noise3.png'
plot 'lsq-noise3.txt'  u 1:2  w l ls 1  lw 2 t "", \
	 'data-noise3.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5
	 
set output 'lsq_out.png'
plot 'lsq-out.txt'  u 1:2  w l ls 1  lw 2 t "", \
	 'data-out.txt' u 1:2 t 'Data points' w p ls 2 lw 3 ps 2.5


