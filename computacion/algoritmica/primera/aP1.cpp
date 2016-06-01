#include <cstdlib>
#include <vector>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <stdint.h>

#include "aP1_error.hpp"
#include "aP1_vector.hpp"
#include "aP1_timing.hpp"
#include "aP1_lineal.hpp"
#include "aP1_quadratic.hpp"
#include "aP1_file.hpp"

int main(int argc, char const *argv[]){
  if(isWrong(argc-1, argv)){
    return EXIT_FAILURE;
  }else{
    unsigned int nMin = atoi(argv[1]);
    unsigned int nMax = atoi(argv[2]);
    unsigned int inc = atoi(argv[3]);
    unsigned int nRep = atoi(argv[4]);
    std::vector<double> nEle;
    std::vector<double> timesB;
    std::vector<double> timesH;
    std::cout << "\nEspere por favor...\n";
    fflush(stdout);
    aP1::timing(nMin, nMax, inc, nRep, nEle, timesB, timesH);
    aP1::Quadratic q;
    double a0q;
    double a1q;
    double a2q;
    double r2;
    q.fit(nEle, timesB, a0q, a1q, a2q, r2);
    std::cout << "\nLa parábola de regresión aplicando el ajuste al método burbuja es:\n\n";
    std::cout << "\t\t\e[37m\e[44m" << a2q << "n²";
    if(a1q >= 0){
      std::cout << "+" << a1q;
    }else{
      std::cout << a1q;
    }
    std::cout << "n";
    if(a0q >= 0){
      std::cout << "+" << a0q << std::endl;
    }else{
      std::cout << a0q << std::endl;
    }
    std::cout << "\e[0m\ny su coeficiente de determinación es:\n\n";
    std::cout << "\t\t\t\e[37m\e[44m" << r2 << std::endl;
    aP1::Lineal l;
    double a0l;
    double a1l;
    l.fit(nEle, timesH, a0l, a1l, r2);
    std::cout << "\e[0m\nLa recta de regresión aplicando el ajuste al método de ordenación por montículo es:\n\n";
    std::cout << "\t\t\e[37m\e[44m" << a1l << "n";
    if(a0l >= 0){
      std::cout << "+" << a0l << std::endl;
    }else{
      std::cout << a0l << std::endl;
    }
    std::cout << "\e[0m\ny su coeficiente de determinación es:\n\n";
    std::cout << "\t\t\t\e[37m\e[44m" << r2 << "\e[0m" << std::endl;
    uint64_t n;
    std::cout << "\e[34m\n¿Desea hacer una estimación de tiempos para un determinado valor del número de elementos? Introduzca el número de elementos o \'0\' si no lo desea: \e[0m";
    std::cin >> n;
    while(n != 0){
      std::cout << "\e[0m\nEl tiempo estimado aplicando el método burbuja para \e[32m" << n << "\e[0m elementos es de \e[37m\e[44m" << (a2q * n * n + a1q * n + a0q) / 86400000000 << "\e[0m días.\n";
      std::cout << "\nEl tiempo estimado aplicando el método de ordenación por montículo para \e[32m" << n << "\e[0m elementos es de \e[37m\e[44m" << (a1l * n + a0q) / 86400000000 << "\e[0m días.\n\n";
      std::cout << "\e[34m\n¿Desea hacer una estimación de tiempos para un determinado valor del número de elementos? Introduzca el número de elementos o \'0\' si no lo desea: \e[0m";
      std::cin >> n;
    }
    std::vector<double> tNSE;
    std::vector<double> tSE;
    q.estimate(nEle, a0q, a1q, a2q, tNSE);
    l.estimate(nEle, a0l, a1l, tSE);
    aP1::saveTimes(nEle, timesB, tNSE, timesH, tSE, "graphic.txt");
  }
  int error = system("chmod u+x gnuplot.sh");
  error = system("./gnuplot.sh");
  char answer;
  std::cout << "\e[34m\n¿Desea observar gráficamente la observación respecto a la estimación de tiempos de ordenación por el método burbuja [\e[32mS\e[34m/\e[31mn\e[34m]: \e[0m";
  std::cin >> answer;
  if(answer == 's' || answer == 'S'){
    error = system("gnome-open 'bubbleGraphic' > /dev/null &");
  }
  std::cout << "\e[34m\n¿Desea observar gráficamente la observación respecto a la estimación de tiempos de ordenación por el método por montículo [\e[32mS\e[34m/\e[31mn\e[34m]: \e[0m";
  std::cin >> answer;
  if(answer == 's' || answer == 'S'){
    error = system("gnome-open 'heapGraphic' > /dev/null &");
  }
  std::cout << "\e[34m\n¿Desea observar gráficamente la observación respecto a la estimación de tiempos de ordenación por los dos métodos [\e[32mS\e[34m/\e[31mn\e[34m]: \e[0m";
  std::cin >> answer;
  if(answer == 's' || answer == 'S'){
    error = system("gnome-open 'methodsGraphic' > /dev/null &");
  }
  std::cout << "\n";
  if(!error){
    return EXIT_SUCCESS;
  }
}
