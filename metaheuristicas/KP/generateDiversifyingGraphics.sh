#!/bin/bash

if (( $# < 1 )) ; then
  echo "./gnuplot args[]"
  exit -1
fi

Colors=('#F44336' '#2196F3' '#0F0F0F' '#009688'
        '#4CAF50' '#9C27B0' '#FFC107' '#FF9800'
        '#795548' '#000000' '#00FF00' '#0000FF'
        );

var=0

echo > gnuplot.in
echo "set key left top" >> gnuplot.in
echo "set xlabel \"Number of Solution\"" >> gnuplot.in
echo "set ylabel \"Profit\"" >> gnuplot.in
echo "set terminal postscript eps color" >> gnuplot.in
echo "set output 'Profit.eps'" >> gnuplot.in
echo -n "plot " >> gnuplot.in


for param in "$@"
do
  if [ -f "$param" ] && [ ${param:0:18} == "profitDiversify_1_" ] && [ ${param:(-16)} == "Sequentially.txt" ]
  then
    echo $param
    echo -n "'${param}' every :::0::1 lt rgb \"${Colors[$((var))]}\" title 'ProfitDiversify' w l, " >> gnuplot.in

    ((var++))
  fi
done
#cat "gnuplot.in" | sed '$s/.$//' > gnuplot.in
gnuplot gnuplot.in

rm gnuplot.in
