#ifndef __TSP_FIRSTNEIGHEXPLORATOR_HPP__
#define __TSP_FIRSTNEIGHEXPLORATOR_HPP__

#include "TSP_Solution.hpp"

namespace TSP {
  class FirstNeighExplorator {
    public:
      FirstNeighExplorator() {}
      FirstNeighExplorator(unsigned int const &limit);

      TSP::Solution explorate(TSP::Solution const &solution);

      /* Código guarro */
      std::vector<double> distances();
      /* Código guarro */

    private:
      unsigned int _limit;

      /* Código guarro */
      std::vector <double> _distances;
      /* Código guarro */
  };
}

#endif
