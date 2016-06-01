#include <string>
#include <fstream>
#include <cassert>
#include <vector>
#include <iostream>

#include "p4_cash.hpp"
#include "p4_currency.hpp"

namespace p4{
  Cash::Cash(std::string const &file_name){
    std::ifstream ifile;
    ifile.open(file_name.c_str());
    assert(ifile.is_open());
    unsigned int value, quantity;
    while(ifile >> value >> quantity){
      Currency c(value, quantity);
      _cash.push_back(c);
    }
    ifile.close();
  }
  unsigned int Cash::get(unsigned int i, unsigned int quantity){
    assert(i < _cash.size());
    assert(quantity <= _cash[i].quantity());
    unsigned int value = _cash[i].value();
    _cash[i].quantity(_cash[i].quantity() - quantity);
    return value * quantity;
  }
  void Cash::sort_by_value(){
    std::vector<Currency> aux_cash;
    while(_cash.size() > 0){
      Currency aux_currency = _cash[0];
      unsigned int position = 0;
      for(int i = 1; i < _cash.size(); i++){
        if(_cash[i] < aux_currency){
          aux_currency = _cash[i];
          position = i;
        }
      }
      aux_cash.push_back(aux_currency);
      _cash.erase(_cash.begin()+position);
    }
    _cash = aux_cash;
  }
  bool Cash::min_change(unsigned int const &value, std::vector<Currency> &change){
    sort_by_value();
    unsigned int actual_value = 0;
    for(int i = _cash.size()-1; i >= 0; i--){
      unsigned int aux_quantity = 0;
      while(_cash[i].value() <= value - actual_value and _cash[i].quantity() > 0){
        actual_value += get(i, 1);
        aux_quantity++;
      }
      if(aux_quantity > 0){
        change.push_back(Currency(_cash[i].value(), aux_quantity));
      }
    }
    if(value == actual_value){
      return true;
    }else{
      return false;
    }
  }
  std::ostream & operator << (std::ostream &stream, Cash const &c){
    stream << "\tVALOR\t" << "\tCANTIDAD" << std::endl;
    for(int i = 0; i < c.cash().size(); i++){
      stream << c.cash()[i] << std::endl;
    }
  }
}
