#include <string>
#include <fstream>
#include <cassert>
#include <vector>
#include <iostream>
#include <limits>

#include "p5_cash.hpp"
#include "p5_currency.hpp"

namespace p5{
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
      for(size_t i = 1; i < _cash.size(); i++){
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
    std::vector<std::vector<unsigned int>> c;
    std::vector<unsigned int> aux(value+1);
    for(size_t i = 0; i < _cash.size(); i++){
      c.push_back(aux);
    }
    for(size_t i = 0; i < _cash.size(); i++){
      c[i][0] = 0;
    }
    for(size_t i = 0; i < _cash.size(); i++){
      for(size_t j = 0; j < value+1; j++){
        if(i == 0 and j < _cash[i].value()){
          c[i][j] = std::numeric_limits<unsigned int>::infinity();
        }else{
          if(i == 0){
            c[i][j] = 1 + c[i][j - _cash[0].value()];
          }else{
            if(j < _cash[i].value()){
              c[i][j] = c[i - 1][j];
            }else{
              c[i][j] = std::min(c[i - 1][j], 1 + c[i][j - _cash[i].value()]);
            }
          }
        }
      }
    }
    /*for(int i = 0; i < _cash.size(); i++){
      for(int j = 0; j < value+1; j++){
        std::cout << c[i][j] << "\t";
      }
      std::cout << std::endl;
    }*/
    unsigned int actual_value = 0;
    unsigned int aux_quantity = 0;
    int i = _cash.size()-1;
    int j = value;
    while(i >= 0 and c[i][j] != 0){
      if(i-1 >= 0 and c[i][j] == c[i-1][j]){
        change.push_back(Currency(_cash[i].value(), aux_quantity));
        i--;
        aux_quantity = 0;
      }else{
        actual_value += get(i, 1);
        aux_quantity++;
        j = j - _cash[i].value();
      }
    }
    change.push_back(Currency(_cash[i].value(), aux_quantity));
    for(size_t i = 0; i < change.size(); i++){
      if(change[i].quantity() == 0){
        change.erase(change.begin()+i);
        i--;
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
    for(size_t i = 0; i < c.cash().size(); i++){
      stream << c.cash()[i] << std::endl;
    }
    return stream;
  }
}
