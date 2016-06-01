#ifndef __KP_GRASP_HPP__
#define __KP_GRASP_HPP__

#include "KP_Problem.hpp"
#include "KP_Solution.hpp"

namespace KP{
  class GRASP {
    public:
      GRASP (KP::Problem const &problem,
             double const &nIt);

    private:
      KP::Solution _solution;

  };

  class Ratio{
    public:
      double _ratio;
      int _n;

      bool operator <(KP::Ratio const &a){
        return this->_ratio < a._ratio;
      }
  };
}

#endif
