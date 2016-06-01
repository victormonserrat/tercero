#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "methodsGraphic"
set key right bottom
set xlabel "NUMERO DE ELEMENTOS"
set ylabel "TIEMPO (MICROSEGUNDOS)"
plot 'graphic.txt' using 1:2 t "ITERATIVO OBSERVADO", 'graphic.txt' using 1:3 t "ITERATIVO ESTIMADO" w l, 'graphic.txt' using 1:4 t "RECURSIVO OBSERVADO", 'graphic.txt' using 1:5 t "RECURSIVO ESTIMADO" w l
set output "iterativeGraphic"
plot 'graphic.txt' using 1:2 t "ITERATIVO OBSERVADO", 'graphic.txt' using 1:3 t "ITERATIVO ESTIMADO" w l
set output "recursiveGraphic"
plot 'graphic.txt' using 1:4 t "RECURSIVO OBSERVADO", 'graphic.txt' using 1:5 t "RECURSIVO ESTIMADO" w l
_end_
