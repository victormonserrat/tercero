#include "KP_GRASP.hpp"
#include "KP_Instance.hpp"
#include "KP_Problem.hpp"
#include "KP_Object.hpp"
#include "KP_SolGenerator.hpp"
#include "KP_LocalSearch.hpp"
#include "KP_FirstNeighExplorator.hpp"

#include <algorithm>
#include <vector>

/*GUARRO*/
#include <iostream>
/*GUARRO*/

#define LIMIT 1500

KP::GRASP::GRASP (KP::Problem const &problem,
                  double const &nIt){

  std::vector <KP::Ratio> ratios;
  KP::Instance instance;

  for (size_t i = 0; i < problem.objects().size() ; i++) {
    KP::Ratio ratio;
    ratio._n = i;
    ratio._ratio = (double)problem.objects()[i].profit() / (double)problem.objects()[i].weight();
    ratios.push_back(ratio);
  }

  std::sort (ratios.rbegin(), ratios.rend());

  unsigned int weight = 0;
  KP::Solution solution;
  solution.problem(problem);
  std::vector<bool> objects (problem.objects().size(), false);

  for (size_t i = 0 ; i < ratios.size() ; i++) {
    if (problem.objects()[ratios[i]._n].weight() + weight <= problem.knacksack().capacity() ){
      objects[ratios[i]._n] = true;
      weight += problem.objects()[ratios[i]._n].weight();
    }
  }
  solution.objects(objects);

  KP::FirstNeighExplorator firstNeighExplorator (LIMIT);
  KP::LocalSearch localSearch (firstNeighExplorator);
  unsigned long long int bestSolutionProfit = instance.profit(solution);
  _solution = solution;

  /*GUARRO*/
  std::cout << "\E[33m" << bestSolutionProfit << "\e[0m" << std::endl;
  unsigned int nObjects = 0;
  unsigned j = 0;
  /*GUARRO*/
  for (size_t i = 0; i < nIt ; i++) {
    KP::Solution currentSolution = localSearch.search(solution);
    unsigned long long int currentSolutionProfit = instance.profit(currentSolution);
    if (currentSolutionProfit > bestSolutionProfit ){
      j++;
      _solution = currentSolution;
      bestSolutionProfit = currentSolutionProfit;
      /*GUARRO*/
      weight = 0;
      std::cout << "\E[32m" << bestSolutionProfit << "\e[0m" << std::endl;
      for (size_t i = 0 ; i < ratios.size() ; i++) {
        if (currentSolution.objects()[ratios[i]._n]){
          weight += currentSolution.problem().objects()[ratios[i]._n].weight();
        }
      }
      nObjects = 0;
      for (size_t i = 0; i < currentSolution.objects().size(); i++) {
        if (currentSolution.objects()[i]){
          nObjects ++;
        }
      }
      //std::cout << "\tWeight: " << weight << " of " << currentSolution.problem().knacksack().capacity() << "\e[0m" << std::endl;
      /*GUARRO*/
    }
    /*GUARRO*/
    else{
      std::cout << "\E[31m" << currentSolutionProfit << "\e[0m" << std::endl;
    }

    /*GUARRO*/
  }

  /*GUARRO*/
  std::cout << "nObjects: " << nObjects << " and weight: " << weight << " of " << solution.problem().knacksack().capacity() << std::endl;
  std::cout << "Mejora " << j << " veces." << std::endl;
  /*GUARRO*/



}
