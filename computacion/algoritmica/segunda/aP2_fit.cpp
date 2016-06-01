#include <vector>
#include <cstdlib>

#include "aP2_fit.hpp"

double aP2::Fit::sum(std::vector<double> const &v) const{
  double sum = 0.0;
  for(size_t i = 0; i < v.size(); i++){
    sum += v[i];
  }
  return sum;
}
double aP2::Fit::sum2(std::vector<double> const &v) const{
  double sum = 0.0;
  for(size_t i = 0; i < v.size(); i++){
    sum += v[i] * v[i];
  }
  return sum;
}
double aP2::Fit::sum3(std::vector<double> const &v) const{
  double sum = 0.0;
  for(size_t i = 0; i < v.size(); i++){
    sum += v[i] * v[i] * v[i];
  }
  return sum;
}
double aP2::Fit::sum4(std::vector<double> const &v) const{
  double sum = 0.0;
  for(size_t i = 0; i < v.size(); i++){
    sum += v[i] * v[i] * v[i] * v[i];
  }
  return sum;
}
double aP2::Fit::sum5(std::vector<double> const &v) const{
  double sum = 0.0;
  for(size_t i = 0; i < v.size(); i++){
    sum += v[i] * v[i] * v[i] * v[i] * v[i];
  }
  return sum;
}
double aP2::Fit::sum6(std::vector<double> const &v) const{
  double sum = 0.0;
  for(size_t i = 0; i < v.size(); i++){
    sum += v[i] * v[i] * v[i] * v[i] * v[i] * v[i];
  }
  return sum;
}
double aP2::Fit::sumXiYi(std::vector<double> const &x, std::vector<double> const &y) const{
  double sum = 0.0;
  for(size_t i = 0; i < x.size(); i++){
    sum += x[i] * y[i];
  }
  return sum;
}
double aP2::Fit::sumXi2Yi(std::vector<double> const &x, std::vector<double> const &y) const{
  double sum = 0.0;
  for(size_t i = 0; i < x.size(); i++){
    sum += x[i] * x[i] * y[i];
  }
  return sum;
}
double aP2::Fit::sumXi3Yi(std::vector<double> const &x, std::vector<double> const &y) const{
  double sum = 0.0;
  for(size_t i = 0; i < x.size(); i++){
    sum += x[i] * x[i] * x[i] * y[i];
  }
  return sum;
}
double aP2::Fit::sumXY2(std::vector<double> const &x, double const &y) const{
  double sumXY2 = 0.0;
  for(size_t i = 0; i < x.size(); i++){
    sumXY2 += (x[i] - y) * (x[i] - y);
  }
  return sumXY2;
}
double aP2::Fit::sc(std::vector<double> const &estimatedY, std::vector<double> const &timesY) const{
  double avEY = sum(estimatedY) / estimatedY.size();
  double avY = sum(timesY) / timesY.size();
  double scE = sumXY2(estimatedY, avEY);
  double scG = sumXY2(timesY, avY);
  return scE / scG;
}
