#include "TSP_LocalSearch.hpp"
#include "TSP_Solution.hpp"
#include "TSP_FirstNeighExplorator.hpp"
#include "TSP_BestNeighExplorator.hpp"

TSP::LocalSearch::LocalSearch(TSP::FirstNeighExplorator const &firstNeighExplorator) {
  _firstNeighExplorator = firstNeighExplorator;
  _isFirstNeighExplorator = true;
  _isBestNeighExplorator = false;
}

TSP::LocalSearch::LocalSearch(TSP::BestNeighExplorator const &bestNeighExplorator) {
  _bestNeighExplorator = bestNeighExplorator;
  _isBestNeighExplorator = true;
  _isFirstNeighExplorator = false;
}

TSP::Solution TSP::LocalSearch::search(TSP::Solution const &solution) {
  if(_isBestNeighExplorator) {
    return _bestNeighExplorator.explorate(solution);
  } else if (_isFirstNeighExplorator) {
    return _firstNeighExplorator.explorate(solution);
  } else {
    return solution;
  }
}

/* Código guarro */
std::vector<double> TSP::LocalSearch::distances(){
  if(_isBestNeighExplorator) {
    return _bestNeighExplorator.distances();
  } else if (_isFirstNeighExplorator) {
    return _firstNeighExplorator.distances();
  }
}
/*Código guarro */
