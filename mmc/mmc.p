set term post eps enhanced color solid lw 1 size 5.0, 3.5 "Arial" 24
set output "mmc.eps"
set title "OpenMP Matriz x Vector Function" noenhanced
set xlabel "Processors ({/Ital n})"
set ylabel "Time ({/Ital Seconds})"
set key left
set grid
set xtics("1P" 1, "2P" 2, "4P" 4, "8P" 8, "16P" 16)
plot "mmc.dat" using 1:2 title "Performance" with lines
