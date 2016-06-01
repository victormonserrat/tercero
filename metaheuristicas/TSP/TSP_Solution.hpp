#ifndef __TSP_SOLUTION_HPP__
#define __TSP_SOLUTION_HPP__

#include "TSP_Problem.hpp"

#include <vector>

namespace TSP {
  class Solution {
    public:
      Solution() {}
      Solution( TSP::Problem const &problem );

      TSP::Problem              problem() const;
      void                      problem(TSP::Problem const &problem);
      std::vector<unsigned int> order() const;
      void                      order(std::vector<unsigned int> const &order);
      std::vector<double>       distances() const;
      void                      distances(std::vector<double> const &distances);

    private:
      TSP::Problem              _problem;
      std::vector<unsigned int> _order;
      std::vector<double>       _distances;
  };
}

#endif
