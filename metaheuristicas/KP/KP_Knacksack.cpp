#include "KP_Knacksack.hpp"

KP::Knacksack::Knacksack( unsigned int const &capacity ) {
  _capacity = capacity;
}

unsigned int KP::Knacksack::capacity() const {
  return _capacity;
}
