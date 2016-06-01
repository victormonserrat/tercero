#include "TSP_SolGenerator.hpp"
#include "TSP_Solution.hpp"

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>

/**/
#include <iostream>
/**/

TSP::SolGenerator::SolGenerator( TSP::Solution const &solution ) {
  _solution = solution;
}

std::vector<TSP::Solution> TSP::SolGenerator::generate( unsigned int const &n ) {
  std::vector<TSP::Solution> solutions;

  while(solutions.size() < n) {
    TSP::Solution solution = _solution;
    std::vector<unsigned int> order = solution.order();
    std::vector<double> distances = solution.distances();

    unsigned int i = rand() % order.size();
    unsigned int j = rand() % order.size();
    if(i != j) {
      if(i > j) {
        unsigned int tmp = j;
        j = i;
        i = tmp;
      }
    }

    std::reverse(order.begin()+i, order.begin()+j+1);
    std::reverse(distances.begin()+i, distances.begin()+j);
    distances[(i-1) % distances.size()] =
    sqrt(
      pow(
        solution.problem().nodes()[order[(i-1) % order.size()]].x()
        -
        solution.problem().nodes()[order[i % order.size()]].x()
      , 2)
      +
      pow(
        solution.problem().nodes()[order[(i-1) % order.size()]].y()
        -
        solution.problem().nodes()[order[i % order.size()]].y()
      , 2)
    );
    distances[j] =
    sqrt(
      pow(
        solution.problem().nodes()[order[j]].x()
        -
        solution.problem().nodes()[order[(j+1) % order.size()]].x()
      , 2)
      +
      pow(
        solution.problem().nodes()[order[j]].y()
        -
        solution.problem().nodes()[order[(j+1) % order.size()]].y()
      , 2)
    );

    solution.order(order);
    solution.distances(distances);

    solutions.push_back(solution);
  }


  return solutions;
}
