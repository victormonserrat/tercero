#include "KP_LocalSearch.hpp"
#include "KP_Solution.hpp"
#include "KP_FirstNeighExplorator.hpp"
#include "KP_BestNeighExplorator.hpp"

KP::LocalSearch::LocalSearch(KP::FirstNeighExplorator const &firstNeighExplorator) {
  _firstNeighExplorator = firstNeighExplorator;
  _isFirstNeighExplorator = true;
  _isBestNeighExplorator = false;
}

KP::LocalSearch::LocalSearch(KP::BestNeighExplorator const &bestNeighExplorator) {
  _bestNeighExplorator = bestNeighExplorator;
  _isBestNeighExplorator = true;
  _isFirstNeighExplorator = false;
}

KP::Solution KP::LocalSearch::search(KP::Solution const &solution) {
  if(_isBestNeighExplorator) {
    return _bestNeighExplorator.explorate(solution);
  } else if (_isFirstNeighExplorator) {
    return _firstNeighExplorator.explorate(solution);
  } else {
    return solution;
  }
}

/* Código guarro */
std::vector<unsigned long long int> KP::LocalSearch::profits(){
  if(_isBestNeighExplorator) {
    return _bestNeighExplorator.profits();
  } else if (_isFirstNeighExplorator) {
    return _firstNeighExplorator.profits();
  }
}
/*Código guarro */
