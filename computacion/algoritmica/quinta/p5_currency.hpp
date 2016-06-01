#ifndef __P5_CURRENCY_HPP__
#define __P5_CURRENCY_HPP__

#include <iostream>

namespace p5{
  class Currency{
  public:
    Currency(unsigned int const &value, unsigned int const &quantity);
    unsigned int value() const{return _value;}
    void value(unsigned int const &value){_value = value;}
    unsigned int quantity() const{return _quantity;}
    void quantity(unsigned int const &quantity){_quantity = quantity;}
    friend std::ostream & operator << (std::ostream &stream, Currency const &c);
    bool operator < (Currency const &c) const;
  private:
    unsigned int _value;
    unsigned int _quantity;
  };
}

#endif
