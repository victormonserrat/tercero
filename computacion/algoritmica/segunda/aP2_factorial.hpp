#ifndef __AP2_FACTORIAL_HPP__
#define __AP2_FACTORIAL_HPP__

#include <vector>

#include "aP2_fit.hpp"

namespace aP2{
  class Factorial : public Fit{
  public:
    Factorial(){}
    ~Factorial(){}
    double factorial(double const &x);
    void fit(const std::vector<double> &x, const std::vector<double> &y);
    void estimate(std::vector<double> const &x, std::vector<double> &estimated);
    double estimate(double const &x);
    inline double a() const{return _a;}
    inline double b() const{return _b;}
  private:
    double _a, _b;
  };
}

#endif
