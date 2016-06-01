#ifndef __TSP_LOCALSEARCH_HPP__
#define __TSP_LOCALSEARCH_HPP__

#include "TSP_Solution.hpp"
#include "TSP_FirstNeighExplorator.hpp"
#include "TSP_BestNeighExplorator.hpp"

namespace TSP {
  class LocalSearch {
    public:
      LocalSearch(TSP::FirstNeighExplorator const &firstNeighExplorator);
      LocalSearch(TSP::BestNeighExplorator const &bestNeighExplorator);

      TSP::Solution search(TSP::Solution const &solution);

      /* Código guarro */
      std::vector<double> distances();
      /* Código guarro */

    private:
      TSP::FirstNeighExplorator _firstNeighExplorator;
      bool _isFirstNeighExplorator;
      TSP::BestNeighExplorator _bestNeighExplorator;
      bool _isBestNeighExplorator;
  };
}

#endif
