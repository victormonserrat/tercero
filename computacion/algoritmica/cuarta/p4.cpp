#include <cstdlib>
#include <iostream>

#include "p4_cash.hpp"
#include "p4_currency.hpp"

int main(int argc, char const *argv[]){
  p4::Cash cash("p4_cash.txt");
  std::cout << "Introduzca el valor del cambio (en céntimos de €): ";
  unsigned int value;
  std::cin >> value;
  std::vector<p4::Currency> c;
  if(!cash.min_change(value, c)){
    std::cout << "No es posible obtener el valor exacto del cambio introducido, lo más aproximado es:" << std::endl;
  }
  p4::Cash change(c);
  std::cout << change;
  return EXIT_SUCCESS;
}
