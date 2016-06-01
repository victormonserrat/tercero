#ifndef __KP_PROBLEM_HPP__
#define __KP_PROBLEM_HPP__

#include "KP_Knacksack.hpp"
#include "KP_Object.hpp"

#include <vector>

namespace KP {
  class Problem {
    public:
      Problem() {}
      Problem(
        KP::Knacksack           const &knacksack,
        std::vector<KP::Object> const &objects
      );

      KP::Knacksack           knacksack() const;
      std::vector<KP::Object> objects() const;

    private:
      KP::Knacksack           _knacksack;
      std::vector<KP::Object> _objects;
  };
}

#endif
