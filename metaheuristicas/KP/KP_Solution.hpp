#ifndef __KP_SOLUTION_HPP__
#define __KP_SOLUTION_HPP__

#include "KP_Problem.hpp"

#include <vector>

namespace KP {
  class Solution {
    public:
      Solution() {}
      Solution( KP::Problem const &problem );

      KP::Problem       problem() const;
      void              problem(KP::Problem const &problem);
      std::vector<bool> objects() const;
      void              objects(std::vector<bool> const &objects);
      void              object(int const &position, bool const &data);

    private:
      KP::Problem       _problem;
      std::vector<bool> _objects;
  };
}

#endif
