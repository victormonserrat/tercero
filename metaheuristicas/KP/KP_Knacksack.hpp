#ifndef __KP_KNACKSACK_HPP__
#define __KP_KNACKSACK_HPP__

namespace KP {
  class Knacksack {
    public:
      Knacksack() {}
      Knacksack(
        unsigned int const &capacity
      );

      unsigned int capacity() const;

    private:
      unsigned int _capacity;
  };
}

#endif
