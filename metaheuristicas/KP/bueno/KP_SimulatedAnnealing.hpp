#ifndef __KP_SIMULATEDANNEALING_HPP__
#define __KP_SIMULATEDANNEALING_HPP__

#include "KP_Solution.hpp"
#include "KP_Instance.hpp"

namespace KP{
  class SimulatedAnnealing {
    public:
      SimulatedAnnealing () {}
      SimulatedAnnealing (KP::Solution const &solution,
                          double const &deltaE0,
                          double const &probability0,
                          double const &nIt);

      void cool (int const &it);

      bool accept (double const &t, double const &deltaE);

      inline KP::Solution bestSolution (){
        return _bestSolution;
      }

    private:
      KP::Solution _bestSolution;
      double _t;
      double _t0;
      //int _nIt;
  };
}

#endif
