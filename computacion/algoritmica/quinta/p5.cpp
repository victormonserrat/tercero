#include <cstdlib>
#include <iostream>

#include "p5_cash.hpp"
#include "p5_currency.hpp"

int main(int argc, char const *argv[]){
  p5::Cash cash("p5_cash.txt");
  std::cout << "Introduzca el valor del cambio (en céntimos de €): ";
  unsigned int value;
  std::cin >> value;
  std::vector<p5::Currency> c;
  if(!cash.min_change(value, c)){
    std::cout << "No es posible obtener el valor exacto del cambio introducido, lo más aproximado es:" << std::endl;
  }
  p5::Cash change(c);
  std::cout << change;
  return EXIT_SUCCESS;
}
