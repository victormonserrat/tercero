#ifndef __AP2_FIT_HPP__
#define __AP2_FIT_HPP__

#include <vector>

namespace aP2{
  class Fit{
  public:
    Fit(){}
    ~Fit(){}
    virtual void fit(const std::vector<double> &x, const std::vector<double> &y) = 0;
    virtual void estimate(std::vector<double> const &x, std::vector<double> &estimated) = 0;
    virtual double estimate(double const &x) = 0;
    double sc(std::vector<double> const &estimatedY, std::vector<double> const &timesY) const;
  protected:
    double sum(std::vector<double> const &v) const;
    double sum2(std::vector<double> const &v) const;
    double sum3(std::vector<double> const &v) const;
    double sum4(std::vector<double> const &v) const;
    double sum5(std::vector<double> const &v) const;
    double sum6(std::vector<double> const &v) const;
    double sumXiYi(std::vector<double> const &x, std::vector<double> const &y) const;
    double sumXi2Yi(std::vector<double> const &x, std::vector<double> const &y) const;
    double sumXi3Yi(std::vector<double> const &x, std::vector<double> const &y) const;
    double sumXY2(std::vector<double> const &x, double const &y) const;
  };
}

#endif
