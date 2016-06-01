#!/bin/bash

if (( $# < 1 )) ; then
  echo "./gnuplot args[]"
  exit -1
fi

for param in "$@"
do
  echo > gnuplot.in
  if [ -f "$param" ] && [ -f "${param/Diversify/Intensify}" ] && [ ${param:0:18} == "profitDiversify_1_" ]
  then
    echo $param
    echo "set key left top" >> gnuplot.in
    echo "set xlabel \"Number of Solution\"" >> gnuplot.in
    echo "set ylabel \"Profit\"" >> gnuplot.in
    echo "set terminal postscript eps color" >> gnuplot.in
    echo "set output '${param/.txt/}.eps'" >> gnuplot.in
    #echo "plot '${param}' every :::0::1 lt rgb \"#ff0000\" title 'ProfitDiversify', '${param/Diversify/Intensify}' using 1:2 lt rgb \"#0000FF\" title 'ProfitIntensify' w l" >> gnuplot.in
    echo "plot '${param}' every :::0::1 lt rgb \"#ff0000\" title 'ProfitDiversify' w l" >> gnuplot.in

    gnuplot gnuplot.in
  fi
done

rm gnuplot.in
