#include "KP_Problem.hpp"
#include "KP_Knacksack.hpp"
#include "KP_Object.hpp"

#include <vector>

KP::Problem::Problem(
  KP::Knacksack           const &knacksack,
  std::vector<KP::Object> const &objects
) {
  _knacksack = knacksack;
  _objects   = objects;
}

KP::Knacksack KP::Problem::knacksack() const {
  return _knacksack;
}

std::vector<KP::Object> KP::Problem::objects() const {
  return _objects;
}
