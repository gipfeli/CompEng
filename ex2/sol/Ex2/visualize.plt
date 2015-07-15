# png
set terminal png size 800,600 enhanced font 'Verdana,16'

set dgrid3d 30,30
set hidden3d
set output 'data-noise.png'
splot "data-field-noise.txt" u 1:2:3 with lines