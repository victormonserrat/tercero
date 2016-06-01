#ifndef __KP_OBJECT_HPP__
#define __KP_OBJECT_HPP__

namespace KP {
  class Object {
    public:
      Object(
        unsigned int const &profit,
        unsigned int const &weight
      );

      unsigned int profit() const;
      unsigned int weight() const;

    private:
      unsigned int _profit;
      unsigned int _weight;
  };
}

#endif
