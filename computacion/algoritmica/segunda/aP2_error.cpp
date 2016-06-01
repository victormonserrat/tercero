#include <iostream>
#include <cstdlib>

#include "aP2_error.hpp"

bool aP2::isWrong(int argc, char const *argv[]){
  if(argc != 4){
    std::cout << "\n\e[31mError de sintaxis: .../aP1 <nMin> <nMax> <inc> <nRep>\e[0m\n\n";
    return true;
  }else if(atoi(argv[1]) < 1 or atoi(argv[2]) < 1 or atoi(argv[3]) < 1 or atoi(argv[4]) < 1){
    std::cout << "\n\e[31mError: Todos los argumentos deben ser positivos\e[0m\n\n";
    return true;
  }else if(atoi(argv[1]) > atoi(argv[2])){
    std::cout << "\n\e[31mError: <nMin> no puede ser mayor que <nMax>\e[0m\n\n";
    return true;
  }else if((atoi(argv[2]) - atoi(argv[1])) / atoi(argv[3]) < 2){
    std::cout << "\n\e[31mError: Los parámetros deben posibilitar al menos 2 incrementos\e[0m\n\n";
    return true;
  }else{
    return false;
  }
}
