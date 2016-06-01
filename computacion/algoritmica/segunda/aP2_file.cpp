#include <vector>
#include <string>
#include <fstream>

#include "aP2_file.hpp"

void aP2::saveTimes(std::vector<double> const &n, std::vector<double> const &tNS, std::vector<double> const &tNSE, std::vector<double> const &tS, std::vector<double> const &tSE, std::string file){
  std::ofstream f(file.c_str());
  for(size_t i = 0; i < n.size(); i++){
    f << n[i] << " " << tNS[i] << " " << tNSE[i] << " " << tS[i] << " " << tSE[i] << std::endl;
  }
  f.close();
}
