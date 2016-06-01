#ifndef __KP_BESTNEIGHEXPLORATOR_HPP__
#define __KP_BESTNEIGHEXPLORATOR_HPP__

#include "KP_Solution.hpp"

namespace KP {
  class BestNeighExplorator {
    public:
      BestNeighExplorator() {}
      BestNeighExplorator(unsigned int const &limit);

      KP::Solution explorate(KP::Solution const &solution);

      /* Código guarro */
      std::vector<unsigned long long int> profits();
      /* Código guarro */

    private:
      unsigned int _limit;
      /* Código guarro */
      std::vector <unsigned long long int> _profits;
      /* Código guarro */
  };
}

#endif
