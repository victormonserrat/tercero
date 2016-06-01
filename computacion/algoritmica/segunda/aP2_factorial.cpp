#include <cstdlib>

#include "aP2_factorial.hpp"
#include "matriz.hpp"
#include "aP2_det.hpp"

double aP2::Factorial::factorial(double const &x){
  double ret = 1.0;
  for(size_t i = x; i > 1; i--){
    ret *= i;
  }
  return ret;
}

void aP2::Factorial::fit(const std::vector<double> &x, const std::vector<double> &y){
  double n = x.size();
  double xi = sum(x);
  double xi2 = sum2(x);
  double yi = sum(y);
  double xiyi = sumXiYi(x, y);
  Matriz<double> mden(2, 2);
  mden.elemento(1, 1, n);   mden.elemento(1, 2, xi);
  mden.elemento(2, 1, xi);  mden.elemento(2, 2, xi2);
  double den = aP2::determinanteIterativo(mden);
  Matriz<double> mb = mden;
  mb.elemento(1, 1, yi);
  mb.elemento(2, 1, xiyi);
  _b = aP2::determinanteIterativo(mb) / den;
  Matriz<double> ma = mden;
  ma.elemento(1, 2, yi);
  ma.elemento(2, 2, xiyi);
  _a = aP2::determinanteIterativo(ma) / den;
}
void aP2::Factorial::estimate(std::vector<double> const &x, std::vector<double> &estimated){
  assert(estimated.empty());
  for(size_t i = 0; i < x.size(); i++){
    estimated.push_back(_a*x[i] + _b);
  }
}
double aP2::Factorial::estimate(double const &x){
  return _a*x + _b;
}
