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

#define LIMIT 100

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

  std::cout<< "Capacity: " << problem.knacksack().capacity() << std::endl;
  for (size_t i = 0 ; i < ratios.size() ; i++) {
    if (problem.objects()[ratios[i]._n].weight() + weight <= problem.knacksack().capacity() ){
      //objects.push_back(true);
      objects[ratios[i]._n] = true;
      std::cout << "true" << std::endl;
      weight += problem.objects()[ratios[i]._n].weight();
    }
    else{
      //objects.push_back(false);
      //std::cout << "false" << std::endl;
    }
  }
  solution.objects(objects);

  KP::FirstNeighExplorator firstNeighExplorator (LIMIT);
  KP::LocalSearch localSearch (firstNeighExplorator);
  unsigned long long int bestSolutionProfit = instance.profit(solution);
  _solution = solution;

  /*GUARRO*/
  std::cout << "bestSolutionProfit: " << bestSolutionProfit << std::endl;
  /*GUARRO*/
  for (size_t i = 0; i < nIt ; i++) {

    /**/
    unsigned int weight = 0;
    for( size_t i = 0; i < solution.problem().objects().size(); i++ ) {
      if ( solution.objects()[i] ) {
        weight += solution.problem().objects()[i].weight();
      }
    }
    fflush(stdout);
    /**/


    KP::Solution currentSolution = localSearch.search(solution);
    unsigned long long int currentSolutionProfit = instance.profit(currentSolution);
    if (currentSolutionProfit > bestSolutionProfit ){
      _solution = currentSolution;
      bestSolutionProfit = currentSolutionProfit;
      /*GUARRO*/
      std::cout << "\E[32mbestSolutionProfit: " << bestSolutionProfit << "\e[0m" << std::endl;
      /*GUARRO*/
    }
    /*GUARRO*/
    else std::cout << "\E[31mNo mejora: \e[0m" << std::endl;
    /*GUARRO*/
  }

}
