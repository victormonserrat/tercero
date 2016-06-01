#include "KP_Object.hpp"

KP::Object::Object(
  unsigned int const &profit,
  unsigned int const &weight
) {
  _profit = profit;
  _weight = weight;
}

unsigned int KP::Object::profit() const {
  return _profit;
}

unsigned int KP::Object::weight() const {
  return _weight;
}
