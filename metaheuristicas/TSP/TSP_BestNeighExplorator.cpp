#include "TSP_BestNeighExplorator.hpp"
#include "TSP_Solution.hpp"
#include "TSP_SolGenerator.hpp"
#include "TSP_Instance.hpp"

TSP::BestNeighExplorator::BestNeighExplorator(unsigned int const &limit) {
  _limit = limit;
}

TSP::Solution TSP::BestNeighExplorator::explorate(TSP::Solution const &solution) {
  TSP::SolGenerator tmp(solution);
  std::vector<TSP::Solution> solutions;
  TSP::Instance aux;
  TSP::Solution best = solution;
  double bestDistance = aux.distance(solution);

  solutions = tmp.generate(_limit);
  for(unsigned int i = 0; i < _limit; i++) {
    double distance = aux.distance(solutions[i]);
    /* Código guarro */
    _distances.push_back(distance);
    /* Código guarro*/
    if(distance < bestDistance) {
      best = solutions[i];
      bestDistance = distance;
    }
  }
  return best;
}

/* Código guarro */
std::vector<double> TSP::BestNeighExplorator::distances(){
  return _distances;
}
/* Código guarro */
