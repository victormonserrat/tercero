#include <cstdlib>
#include <ctime>
#include <iostream>

#include "aP2_matrix.hpp"
#include "matriz.hpp"

void aP2::fill(Matriz<double> &m, double const &min, double const &max){
  srand(time(NULL));
  for(size_t i = 0; i < m.filas(); i++){
    for(size_t j = 0; j < m.columnas(); j++){
      m.elemento(i+1, j+1, (((double) rand()) / ((double) RAND_MAX)) * (max - min) + min);
    }
  }
}
