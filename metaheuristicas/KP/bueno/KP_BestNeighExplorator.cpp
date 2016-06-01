#include "KP_BestNeighExplorator.hpp"
#include "KP_Solution.hpp"
#include "KP_SolGenerator.hpp"
#include "KP_Instance.hpp"

/* Código guarro */
#include <vector>
/* Código guarro */

KP::BestNeighExplorator::BestNeighExplorator(unsigned int const &limit) {
  _limit = limit;
}

KP::Solution KP::BestNeighExplorator::explorate(KP::Solution const &solution) {
  KP::SolGenerator tmp(solution);
  std::vector<KP::Solution> solutions;
  KP::Instance aux;
  KP::Solution best = solution;
  unsigned long long int bestProfit = aux.profit(solution);

  solutions = tmp.generate(_limit);
  for(unsigned int i = 0; i < _limit; i++) {
    unsigned long long int profit = aux.profit(solutions[i]);
    /* Código guarro */
    _profits.push_back(profit);
    /* Código guarro*/

    if(profit > bestProfit) {
      best = solutions[i];
      bestProfit = profit;
    }
  }
  return best;
}

/* Código guarro */
std::vector<unsigned long long int> KP::BestNeighExplorator::profits(){
  return _profits;
}
/* Código guarro */
