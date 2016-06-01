#include "KP_FirstNeighExplorator.hpp"
#include "KP_Solution.hpp"
#include "KP_SolGenerator.hpp"
#include "KP_Instance.hpp"

/* Código guarro */
#include <vector>
/* Código guarro */

KP::FirstNeighExplorator::FirstNeighExplorator(unsigned int const &limit) {
  _limit = limit;
}

KP::Solution KP::FirstNeighExplorator::explorate(KP::Solution const &solution) {
  KP::SolGenerator tmp(solution);
  std::vector<KP::Solution> solutions;
  KP::Instance aux;

  for(unsigned int i = 0; i < _limit; i++) {
    solutions = tmp.generate(1);
    /* Código guarro */
    _profits.push_back(aux.profit(solutions[0]));
    /* Código guarro*/
    if(aux.profit(solutions[0]) > aux.profit(solution)) {
      return solutions[0];
    }
  }
  return solution;
}

/* Código guarro */
std::vector<unsigned long long int> KP::FirstNeighExplorator::profits(){
  return _profits;
}
/* Código guarro */
