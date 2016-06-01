#ifndef __TSP_SIMULATEDANNEALING_HPP__
#define __TSP_SIMULATEDANNEALING_HPP__

#include "TSP_Solution.hpp"
#include "TSP_Instance.hpp"

namespace TSP{
  class SimulatedAnnealing {
    public:
      SimulatedAnnealing () {}
      SimulatedAnnealing (TSP::Solution const &solution,
                          double const &deltaE0,
                          double const &probability0,
                          double const &nIt);

      void cool (int const &it);

      bool accept (double const &t, double const &deltaE);

      inline TSP::Solution bestSolution (){
        return _bestSolution;
      }

    private:
      TSP::Solution _bestSolution;
      double _t;
      double _t0;
  };
}

#endif
