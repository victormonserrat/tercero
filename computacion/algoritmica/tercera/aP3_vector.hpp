#ifndef __AP3_VECTOR_HPP__
#define __AP3_VECTOR_HPP__

#include <vector>

namespace aP3{
  void fillVector(std::vector<int> &v, int const &n);
  int Maximo(int &a, int &b);
  int Minimo(int &a, int &b);
  void MaximoMinimo(std::vector<int> &v, int n, int i, int j, int &maximo, int &minimo, int &nCalls);
}

#endif
