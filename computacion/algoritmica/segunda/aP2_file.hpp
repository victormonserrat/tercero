#ifndef __AP2_FILE_HPP__
#define __AP2_FILE_HPP__

#include <vector>
#include <string>

namespace aP2{
  void saveTimes(std::vector<double> const &n, std::vector<double> const &tNS, std::vector<double> const &tNSE, std::vector<double> const &tS, std::vector<double> const &tSE, std::string file);
}

#endif
