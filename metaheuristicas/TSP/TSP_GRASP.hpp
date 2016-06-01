#ifndef __TSP_GRASP_HPP__
#define __TSP_GRASP_HPP__

#include "TSP_Problem.hpp"
#include "TSP_Solution.hpp"
#include "TSP_Node.hpp"

namespace TSP{
  class GRASP {
    public:
      GRASP (TSP::Problem const &problem,
             double const &nIt);

    private:
      TSP::Solution _solution;

  };
}

#endif
