#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>

#include "aP3_vector.hpp"

void aP3::fillVector(std::vector<int> &v, int const &n){
  assert(v.empty());
  std::srand(std::time(NULL));
  for(int i = 0; i < n; i++) {
    int aux = rand() % 10000;
    v.push_back(aux);
  }
}
int aP3::Maximo(int &a, int &b){
  if(a > b){
    return a;
  }else{
    return b;
  }
}
int aP3::Minimo(int &a, int &b){
  if(a < b){
    return a;
  }else{
    return b;
  }
}
void aP3::MaximoMinimo(std::vector<int> &v, int n, int i, int j, int &maximo, int &minimo, int &nCalls){
  nCalls++;
  if(i == j){
    maximo = v[i];
    minimo = v[i];
  }else{
    if(i == j-1){
      if(v[i] < v[j]){
        maximo = v[j];
        minimo = v[i];
      }else{
        maximo = v[i];
        minimo = v[j];
      }
    }else{
      int mitad = (i+j)/2;
      int minimo1, maximo1, minimo2, maximo2;
      aP3::MaximoMinimo(v, n, i, mitad, maximo1, minimo1, nCalls);
      aP3::MaximoMinimo(v, n, mitad+1, j, maximo2, minimo2, nCalls);
      maximo = aP3::Maximo(maximo1, maximo2);
      minimo = aP3::Minimo(minimo1, minimo2);
    }
  }
}
