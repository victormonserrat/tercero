#include <vector>
#include <cstdlib>
#include <iostream>

#include "aP3_vector.hpp"

int main(int argc, char const *argv[]){
  std::vector<int> v;
  int n;
  int maximo;
  int minimo;
  int nCalls = 0;
  std::cout << "Introduzca el número de elementos: ";
  std::cin >> n;
  std::cout << std::endl;
  aP3::fillVector(v, n);
  std::cout << "\tVector: " << std::endl;
  for(int i = 0; i < n; i++){
    std::cout << "\t\t" << v[i] << std::endl;
  }
  std::cout << std::endl;
  aP3::MaximoMinimo(v, n-1, 0, n-1, maximo, minimo, nCalls);
  std::cout << "Máximo: " << maximo << std::endl;
  std::cout << "Mínimo: " << minimo << std::endl;
  std::cout << "Número de llamadas recursivas: " << nCalls << std::endl;
  return EXIT_SUCCESS;
}
