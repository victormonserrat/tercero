#include <cassert>
#include <cstdlib>

#include "aP2_cubic.hpp"
#include "matriz.hpp"
#include "aP2_det.hpp"

void aP2::Cubic::fit(const std::vector<double> &x, const std::vector<double> &y){
  double n = x.size();
  double xi = sum(x);
  double xi2 = sum2(x);
  double xi3 = sum3(x);
  double xi4 = sum4(x);
  double xi5 = sum5(x);
  double xi6 = sum6(x);
  double yi = sum(y);
  double xiyi = sumXiYi(x, y);
  double xi2yi = sumXi2Yi(x, y);
  double xi3yi = sumXi3Yi(x, y);
  Matriz<double> mden(4, 4);
  mden.elemento(1, 1, n);   mden.elemento(1, 2, xi);
  mden.elemento(1, 3, xi2); mden.elemento(1, 4, xi3);
  mden.elemento(2, 1, xi);  mden.elemento(2, 2, xi2);
  mden.elemento(2, 3, xi3); mden.elemento(2, 4, xi4);
  mden.elemento(3, 1, xi2); mden.elemento(3, 2, xi3);
  mden.elemento(3, 3, xi4); mden.elemento(3, 4, xi5);
  mden.elemento(4, 1, xi3); mden.elemento(4, 2, xi4);
  mden.elemento(4, 3, xi5); mden.elemento(4, 4, xi6);
  double den = aP2::determinanteIterativo(mden);
  Matriz<double> ma0 = mden;
  ma0.elemento(1, 1, yi);    ma0.elemento(2, 1, xiyi);
  ma0.elemento(3, 1, xi2yi); ma0.elemento(4, 1, xi3yi);
  _a0 = aP2::determinanteIterativo(ma0) / den;
  Matriz<double> ma1 = mden;
  ma1.elemento(1, 2, yi);    ma1.elemento(2, 2, xiyi);
  ma1.elemento(3, 2, xi2yi); ma1.elemento(4, 2, xi3yi);
  _a1 = aP2::determinanteIterativo(ma1) / den;
  Matriz<double> ma2 = mden;
  ma2.elemento(1, 3, yi);    ma2.elemento(2, 3, xiyi);
  ma2.elemento(3, 3, xi2yi); ma2.elemento(4, 3, xi3yi);
  _a2 = aP2::determinanteIterativo(ma2) / den;
  Matriz<double> ma3 = mden;
  ma3.elemento(1, 4, yi);    ma3.elemento(2, 4, xiyi);
  ma3.elemento(3, 4, xi2yi); ma3.elemento(4, 4, xi3yi);
  _a3 = aP2::determinanteIterativo(ma3) / den;
}
void aP2::Cubic::estimate(std::vector<double> const &x, std::vector<double> &estimated){
  assert(estimated.empty());
  for(size_t i = 0; i < x.size(); i++){
    estimated.push_back(x[i]*x[i]*x[i]*_a3 + x[i]*x[i]*_a2 + x[i]*_a1 + _a0);
  }
}

double aP2::Cubic::estimate(double const &x){
  return x*x*x*_a3 + x*x*_a2 + x*_a1 + _a0;
}
