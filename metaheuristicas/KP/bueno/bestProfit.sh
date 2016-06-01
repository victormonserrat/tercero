#!/bin/bash

if (( $# < 1 )) ; then
  echo "./gnuplot args[]"
  exit -1
fi

Colors=('#F44336' '#2196F3' '#432288' '#795548'
        '#4CAF50' '#9C27B0' '#FFC107' '#FF9800'
        '#009688' '#000000' '#00FF00' '#0000FF'
        );

var=0

echo > gnuplot.in
echo "set key right bottom" >> gnuplot.in
echo "set xlabel \"Number of Solution\"" >> gnuplot.in
echo "set ylabel \"Profit\"" >> gnuplot.in
echo "set terminal postscript eps color" >> gnuplot.in
echo "set output 'Profit.eps'" >> gnuplot.in
echo -n "plot " >> gnuplot.in


for param in "$@"
do
  if [ -f "$param" ] && [ ${param:0:22} == "bestProfitDiversify_1_" ]
  then
    ite=var+1
    echo $param
    echo -n "'${param}' every :::0::1 lt rgb \"${Colors[$((var))]}\" title 'Iteration $((ite))' w l, " >> gnuplot.in

    ((var++))
  fi
done
#cat "gnuplot.in" | sed '$s/.$//' > gnuplot.in
gnuplot gnuplot.in

rm gnuplot.in
