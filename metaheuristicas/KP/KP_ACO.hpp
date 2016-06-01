#ifndef __KP_ACO_HPP__
#define __KP_ACO_HPP__

#include "KP_Problem.hpp"

namespace KP {
  class ACO {
    public:
      ACO() {}
      ACO(KP::Problem const &problem, int const &nIt);

    private:
      KP::Problem _problem;
      std::vector <unsigned int> _trails;
      std::vector <double> _ratios;

  };
}

#endif
