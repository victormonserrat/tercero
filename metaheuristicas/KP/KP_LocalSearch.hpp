#ifndef __KP_LOCALSEARCH_HPP__
#define __KP_LOCALSEARCH_HPP__

#include "KP_Solution.hpp"
#include "KP_FirstNeighExplorator.hpp"
#include "KP_BestNeighExplorator.hpp"

namespace KP {
  class LocalSearch {
    public:
      LocalSearch(KP::FirstNeighExplorator const &firstNeighExplorator);
      LocalSearch(KP::BestNeighExplorator const &bestNeighExplorator);

      KP::Solution search(KP::Solution const &solution);

      /* Código guarro */
      std::vector<unsigned long long int> profits();
      /* Código guarro */

    private:
      KP::FirstNeighExplorator _firstNeighExplorator;
      bool _isFirstNeighExplorator;
      KP::BestNeighExplorator _bestNeighExplorator;
      bool _isBestNeighExplorator;
  };
}

#endif
