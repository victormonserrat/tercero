#ifndef __KP_SOLGENERATOR_HPP__
#define __KP_SOLGENERATOR_HPP__

#include "KP_Solution.hpp"

#include <vector>

namespace KP {
  class SolGenerator {
    public:
      SolGenerator( KP::Solution const &solution );

      std::vector<KP::Solution> generate( unsigned int const &n );

    private:
      KP::Solution _solution;
  };
}

#endif
