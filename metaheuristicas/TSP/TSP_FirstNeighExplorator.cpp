#include "TSP_FirstNeighExplorator.hpp"
#include "TSP_Solution.hpp"
#include "TSP_SolGenerator.hpp"
#include "TSP_Instance.hpp"

TSP::FirstNeighExplorator::FirstNeighExplorator(unsigned int const &limit) {
  _limit = limit;
}

TSP::Solution TSP::FirstNeighExplorator::explorate(TSP::Solution const &solution) {
  TSP::SolGenerator tmp(solution);
  std::vector<TSP::Solution> solutions;
  TSP::Instance aux;

  for(unsigned int i = 0; i < _limit; i++) {
    solutions = tmp.generate(1);
    /* Código guarro */
    _distances.push_back(aux.distance(solutions[0]));
    /* Código guarro*/
    if(aux.distance(solutions[0]) < aux.distance(solution)) {
      return solutions[0];
    }
  }
  return solution;
}

/* Código guarro */
std::vector<double> TSP::FirstNeighExplorator::distances(){
  return _distances;
}
/* Código guarro */
