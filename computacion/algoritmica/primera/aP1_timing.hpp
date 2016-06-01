#ifndef __AP1_TIME_HPP__
#define __AP1_TIME_HPP__

#include <vector>

namespace aP1{
  void timing(unsigned int const &nMin, unsigned int const &nMax, unsigned int const &inc, unsigned int const &nRep, std::vector<double> &nEle, std::vector<double> &timesB, std::vector<double> &timesH);
}

#endif
