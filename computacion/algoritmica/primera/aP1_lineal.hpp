#ifndef __AP1_LINEAL_HPP__
#define __AP1_LINEAL_HPP__

#include <vector>
#include <cstdlib>
#include <cmath>
#include <cassert>

#include "aP1_fit.hpp"

namespace aP1{
  class Lineal : public Fit{
  public:
    Lineal(){}
    ~Lineal(){}
    void fit(std::vector<double> const &x, std::vector<double> const &y, double &a0, double &a1, double &r2){
      std::vector<double> xlogx;
      for(size_t i = 0; i < x.size(); i++) {
        xlogx.push_back(x[i] * log(x[i]));
      }
      double xi = sum(x);
      double xi2 = sum2(x);
      double xiyi = sumXiYi(x, y);
      double yi = sum(y);
      double n = x.size();
      double den = det(n, xi, xi, xi2);
      a0 = det(yi, xi, xiyi, xi2) / den;
      a1 = det(n, yi, xi, xiyi) / den;
      std::vector<double> estimatedY;
      estimate(xlogx, a0, a1, estimatedY);
      std::vector<double> estimatedYaux;
      estimate(x, a0, a1, estimatedYaux);
      r2 = sc(estimatedYaux, y);
    }
    void estimate(std::vector<double> const &x, double const &a0, double const &a1, std::vector<double> &estimatedY){
      assert(estimatedY.empty());
      for(size_t i = 0; i < x.size(); i++){
        estimatedY.push_back(x[i] * a1 + a0);
      }
    }
  protected:
    double det(double const &a00, double const &a01, double const &a10, double const &a11) const{
      return a00 * a11 - a01 * a10;
    }
  };
}

#endif
