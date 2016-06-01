#ifndef __KP_FIRSTNEIGHEXPLORATOR_HPP__
#define __KP_FIRSTNEIGHEXPLORATOR_HPP__

#include "KP_Solution.hpp"

namespace KP {
  class FirstNeighExplorator {
    public:
      FirstNeighExplorator() {}
      FirstNeighExplorator(unsigned int const &limit);

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
