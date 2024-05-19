clear
reset
set terminal push
set size 1.0, 1.0
set term post eps enhanced color solid lw 1 size 10.0, 7.0 "Helvetica" 24
set grid
set encoding iso_8859_1
set output "mm.all.eps"
set size 1.0, 1.0
set origin 0.0, 0.0
set multiplot
set size 0.5,0.5
set origin 0.0,0.5
#set title "(a) Tiempo de Ejecuci{/E \363}n"
set title "Tiempo de Ejecuci{/E \363}n"
#set key left 
set key right
set xlabel "{/Ital p} (n{/E \372}mero de procesos MPI)"
set ylabel "{/Ital T_p} (segundos)" 
plot "mm.all.dat" using 1:2:xtic(1) notitle with linespoints
set size 0.5,0.5
set origin 0.5,0.5
#set title "(b) Speed-up"
set title "Speed-up"
set key left
#set key right
set xlabel "{/Ital p} (n{/E \372}mero de procesos MPI)"
set ylabel "{/Ital S} = {/Ital T_s} / {/Ital T_p}" 
plot "mm.all.dat" using 1:5:xtic(1) notitle with linespoints
set size 0.5,0.5
set origin 0.0,0.0
#set title "(c) Eficiencia"
set title "Eficiencia"
set key right
set xlabel "{/Ital p} (n{/E \372}mero de procesos MPI)"
set ylabel "{/Ital E} = ({/Ital S} / {/Ital p}) {/Symbol \264} 100 (%)"  
plot "mm.all.dat" using 1:6:xtic(1) notitle with linespoints
set size 0.5,0.5
set origin 0.5,0.0
#set title "(d) Escalabilidad"
set title "Escalabilidad"
set key bottom left
set xlabel "{/Ital p} (n{/E \372}mero de procesos MPI)"
set ylabel "{/Ital SC} = ({/Ital T_{p/2}} / (2 {/Ital T_p})) {/Symbol \264} 100 (%)"  
plot "mm.all.dat" using 1:7:xtic(1) notitle with linespoints
unset multiplot
set output
set terminal pop
