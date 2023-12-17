set terminal wxt size 800,600
set title 'RGB Image Visualization'
set xlabel 'X'
set ylabel 'Y'
set xrange [0:*]
set yrange [0:*]
plot 'image_data.txt' using 1:2:(column(1 + 3)):(column(1 + 3)):(column(1 + 3)) with points pt 7 lc rgb variable title 'RGB Image'
pause -1 'Press any key to exit'
