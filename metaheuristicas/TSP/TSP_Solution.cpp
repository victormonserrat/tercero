#include "TSP_Solution.hpp"
#include "TSP_Problem.hpp"

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>

TSP::Solution::Solution( TSP::Problem const &problem ) {
  _problem = problem;
  unsigned int position;
  std::vector<unsigned int>::iterator i;
  while( _order.size() < problem.nodes().size() ) {
    position = rand() % problem.nodes().size();
    i = std::find( _order.begin(), _order.end(), position );
    if( i == _order.end() ) {
      _order.push_back( position );
    }
  }
  for( size_t i = 0; i < _order.size(); i++ ) {
    double distance =
    sqrt( pow(
              problem.nodes()[_order[i]].x() -
              problem.nodes()[ _order[(i + 1) % _order.size()] ].x(), 2
          ) +
          pow(
              problem.nodes()[_order[i]].y() -
              problem.nodes()[ _order[(i + 1) % _order.size()] ].y(), 2
          )
    );
    _distances.push_back( distance );
  }
}

TSP::Problem TSP::Solution::problem() const {
  return _problem;
}

void TSP::Solution::problem(TSP::Problem const &problem) {
  _problem = problem;
}

std::vector<unsigned int> TSP::Solution::order() const {
  return _order;
}

void TSP::Solution::order(std::vector<unsigned int> const &order) {
  _order = order;
}

std::vector<double> TSP::Solution::distances() const {
  return _distances;
}

void TSP::Solution::distances(std::vector<double> const &distances) {
  _distances = distances;
}
