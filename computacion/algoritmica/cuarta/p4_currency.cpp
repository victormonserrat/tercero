#include <iostream>

#include "p4_currency.hpp"

namespace p4{
  Currency::Currency(unsigned int const &value, unsigned int const &quantity){
    _value = value;
    _quantity = quantity;
  }
  std::ostream & operator << (std::ostream &stream, Currency const &c){
    stream << "\t" << c.value() << "\t\t" << c.quantity();
  };
  bool Currency::operator < (Currency const &c) const{
    if(_value < c.value()){
      return true;
    }else{
      return false;
    }
  }
}
