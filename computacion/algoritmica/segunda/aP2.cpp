#include <cstdlib>
#include <vector>
#include <iostream>

#include "aP2_error.hpp"
#include "aP2_timing.hpp"
#include "aP2_cubic.hpp"
#include "aP2_factorial.hpp"
#include "aP2_file.hpp"

int main(int argc, char const *argv[]){
  if(aP2::isWrong(argc-1, argv)){
    return EXIT_FAILURE;
  }else{
    unsigned int nMin = atoi(argv[1]);
    unsigned int nMax = atoi(argv[2]);
    unsigned int inc = atoi(argv[3]);
    unsigned int nRep = atoi(argv[4]);
    std::vector<double> nEle;
    std::vector<double> timesI;
    std::vector<double> timesR;
    double min, max;
    std::cout << "\e[34m\nIntroduzca el valor mínimo que deben tener los elementos de la matriz: \e[0m";
    std::cin >> min;
    std::cout << "\e[34m\nIntroduzca el valor máximo que deben tener los elementos de la matriz: \e[0m";
    std::cin >> max;
    std::cout << "\nEspere por favor...\n";
    fflush(stdout);
    aP2::timing(nMin, nMax, inc, nRep, nEle, min, max, timesI, timesR);
    aP2::Cubic c;
    c.fit(nEle, timesI);
    aP2::Factorial f;
    std::vector<double> factnEle = nEle;
    for(size_t i = 0; i < factnEle.size(); i++){
      factnEle[i] = f.factorial(factnEle[i]);
    }
    f.fit(factnEle, timesR);
    std::vector<double> estimatedI;
    c.estimate(nEle, estimatedI);
    std::vector<double> estimatedR;
    f.estimate(factnEle, estimatedR);
    std::cout << "\nLa curva de regresión aplicando el ajuste al método iterativo es:\n\n";
    std::cout << "\t\t\e[37m\e[44m" << c.a3() << "n³";
    if(c.a2() >= 0){
      std::cout << "+" << c.a2();
    }else{
      std::cout << c.a2();
    }
    std::cout << "n²";
    if(c.a1() >= 0){
      std::cout << "+" << c.a1();
    }else{
      std::cout << c.a1();
    }
    std::cout << "n";
    if(c.a0() >= 0){
      std::cout << "+" << c.a0() << std::endl;
    }else{
      std::cout << c.a0() << std::endl;
    }
    std::cout << "\e[0m\ny su coeficiente de determinación es:\n\n";
    std::cout << "\t\t\t\e[37m\e[44m" << c.sc(estimatedI, timesI) << std::endl;
    std::cout << "\e[0m\nLa curva de regresión aplicando el método recursivo es:\n\n";
    std::cout << "\t\t\e[37m\e[44m" << f.a() << "n!";
    if(f.b() >= 0){
      std::cout << "+" << f.b() << std::endl;
    }else{
      std::cout << f.b() << std::endl;
    }
    std::cout << "\e[0m\ny su coeficiente de determinación es:\n\n";
    std::cout << "\t\t\t\e[37m\e[44m" << f.sc(estimatedR, timesR) << "\e[0m" << std::endl;
    uint64_t n;
    std::cout << "\e[34m\n¿Desea hacer una estimación de tiempos para un determinado valor del orden de la matriz? Introduzca el orden o \'0\' si no lo desea: \e[0m";
    std::cin >> n;
    while(n != 0){
      std::cout << "\e[0m\nEl tiempo estimado aplicando el método iterativo para una matriz de orden \e[32m" << n << "\e[0m es de \e[37m\e[44m" << c.estimate(n) / 86400000000 << "\e[0m días.\n";
      std::cout << "\nEl tiempo estimado aplicando el método recursivo para una matriz de orden \e[32m" << n << "\e[0m es de \e[37m\e[44m" << f.estimate(f.factorial(n)) / 86400000000 << "\e[0m días.\n\n";
      std::cout << "\e[34m\n¿Desea hacer una estimación de tiempos para un determinado valor del número de elementos? Introduzca el número de elementos o \'0\' si no lo desea: \e[0m";
      std::cin >> n;
    }
    aP2::saveTimes(nEle, timesI, estimatedI, timesR, estimatedR, "graphic.txt");
  }
  int error = system("chmod u+x gnuplot.sh");
  error = system("./gnuplot.sh");
  char answer;
  std::cout << "\e[34m\n¿Desea observar gráficamente la observación respecto a la estimación de tiempos del cálculo del determinante por el método iterativo [\e[32mS\e[34m/\e[31mn\e[34m]: \e[0m";
  std::cin >> answer;
  if(answer == 's' || answer == 'S'){
    error = system("gnome-open 'iterativeGraphic' > /dev/null &");
  }
  std::cout << "\e[34m\n¿Desea observar gráficamente la observación respecto a la estimación de tiempos del cálculo del determinante por el método recursivo [\e[32mS\e[34m/\e[31mn\e[34m]: \e[0m";
  std::cin >> answer;
  if(answer == 's' || answer == 'S'){
    error = system("gnome-open 'recursiveGraphic' > /dev/null &");
  }
  std::cout << "\e[34m\n¿Desea observar gráficamente la observación respecto a la estimación de tiempos del cálculo del determinante por los dos métodos [\e[32mS\e[34m/\e[31mn\e[34m]: \e[0m";
  std::cin >> answer;
  if(answer == 's' || answer == 'S'){
    error = system("gnome-open 'methodsGraphic' > /dev/null &");
  }
  std::cout << "\n";
  if(!error){
    return EXIT_SUCCESS;
  }
}
