#ifndef __AP1_QUADRATIC_HPP__
#define __AP1_QUADRATIC_HPP__

#include <vector>
#include <cassert>
#include <cstdlib>

#include "aP1_fit.hpp"

namespace aP1{
  class Quadratic : public Fit{
  public:
    Quadratic(){}
    ~Quadratic(){}
    void fit(const std::vector<double> &x, const std::vector<double> &y, double &a0, double &a1, double &a2, double &r2){
      double xi = sum(x);
      double xi2 = sum2(x);
      double xi3 = sum3(x);
      double xi4 = sum4(x);
      double xiyi = sumXiYi(x, y);
      double xi2yi = sumXi2Yi(x, y);
      double yi = sum(y);
      double n = x.size();
      double den = det(n, xi, xi2, xi, xi2, xi3, xi2, xi3, xi4);
      a0 = det(yi, xi, xi2, xiyi, xi2, xi3, xi2yi, xi3, xi4) / den;
      a1 = det(n, yi, xi2, xi, xiyi, xi3, xi2, xi2yi, xi4) / den;
      a2 = det(n, xi, yi, xi, xi2, xiyi, xi2, xi3, xi2yi) / den;
      std::vector<double> estimatedY;
      estimate(x, a0, a1, a2, estimatedY);
      r2 = sc(estimatedY, y);
    }
    void estimate(std::vector<double> const &x, double const &a0, double const &a1, double const &a2, std::vector<double> &estimatedY){
      assert(estimatedY.empty());
      for(size_t i = 0; i < x.size(); i++){
        estimatedY.push_back(x[i] * x[i] * a2 + x[i] * a1 + a0);
      }
    }
  protected:
    double sum3(std::vector<double> const &v) const{
      double sum3 = 0.0;
      for(size_t i = 0; i < v.size(); i++){
        sum3 += v[i] * v[i] * v[i];
      }
      return sum3;
    }
    double sum4(std::vector<double> const &v) const{
      double sum4 = 0.0;
      for(size_t i = 0; i < v.size(); i++){
        sum4 += v[i] * v[i] * v[i] * v[i];
      }
      return sum4;
    }
    double sumXi2Yi(std::vector<double> const &x, std::vector<double> const &y) const{
      double sumXi2Yi = 0.0;
      for(size_t i = 0; i < x.size(); i++){
        sumXi2Yi += x[i] * x[i] * y[i];
      }
      return sumXi2Yi;
    }
    double det(double const &a00, double const &a01, double const &a02, double const &a10, double const &a11, double const &a12, double const &a20, double const &a21, double const &a22) const{
      double det = a00 * a11 * a22 + a10 * a21 * a02 + a20 * a01 * a12;
      det -= a02 * a11 * a20 + a12 * a21 * a00 + a22 * a01 * a10;
      return det;
    }
  };
}

#endif
