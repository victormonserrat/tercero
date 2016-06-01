#ifndef __TSP_SOLGENERATOR_HPP__
#define __TSP_SOLGENERATOR_HPP__

#include "TSP_Solution.hpp"

#include <vector>

namespace TSP {
  class SolGenerator {
    public:
      SolGenerator( TSP::Solution const &solution );

      std::vector<TSP::Solution> generate( unsigned int const &n );

    private:
      TSP::Solution _solution;
  };
}

#endif
