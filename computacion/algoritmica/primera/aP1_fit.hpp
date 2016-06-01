#ifndef __AP1_FIT_HPP__
#define __AP1_FIT_HPP__

#include <vector>
#include <cstdlib>

namespace aP1{
  class Fit{
  public:
    Fit(){}
    ~Fit(){}
  protected:
    double sum(std::vector<double> const &v) const{
      double sum = 0.0;
      for(size_t i = 0; i < v.size(); i++){
        sum += v[i];
      }
      return sum;
    }
    double sum2(std::vector<double> const &v) const{
      double sum2 = 0.0;
      for(size_t i = 0; i < v.size(); i++){
        sum2 += v[i] * v[i];
      }
      return sum2;
    }
    double sumXiYi(std::vector<double> const &x, std::vector<double> const &y) const{
      double sumXiYi = 0.0;
      for(size_t i = 0; i < x.size(); i++){
        sumXiYi += x[i] * y[i];
      }
      return sumXiYi;
    }
    double sumXY2(std::vector<double> const &x, double const &y) const{
      double sumXY2 = 0.0;
      for(size_t i = 0; i < x.size(); i++){
        sumXY2 += (x[i] - y) * (x[i] - y);
      }
      return sumXY2;
    }
    double sc(std::vector<double> const &estimatedY, std::vector<double> const &timesY) const{
      double avY = sum(timesY) / timesY.size();
      double avEY = sum(estimatedY) / estimatedY.size();
      double scE = sumXY2(estimatedY, avEY);
      double scG = sumXY2(timesY, avY);
      return scE / scG;
    }
  };
}

#endif
