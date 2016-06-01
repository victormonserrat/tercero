#ifndef __AP2_CUBIC_HPP__
#define __AP2_CUBIC_HPP__

#include <vector>

#include "aP2_fit.hpp"

namespace aP2{
  class Cubic : public Fit{
  public:
    Cubic(){}
    ~Cubic(){}
    void fit(const std::vector<double> &x, const std::vector<double> &y);
    void estimate(std::vector<double> const &x, std::vector<double> &estimated);
    double estimate(double const &x);
    inline double a0() const{return _a0;}
    inline double a1() const{return _a1;}
    inline double a2() const{return _a2;}
    inline double a3() const{return _a3;}
  private:
    double _a0, _a1, _a2, _a3;
  };
}

#endif
