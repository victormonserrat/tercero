#ifndef __P5_CASH_HPP__
#define __P5_CASH_HPP__

#include <string>
#include <vector>
#include <iostream>

#include "p5_currency.hpp"

namespace p5{
  class Cash{
  public:
    Cash(std::string const &file_name);
    Cash(std::vector<Currency> const &cash){_cash = cash;}
    std::vector<Currency> cash() const{return _cash;}
    void cash(std::vector<Currency> cash){_cash = cash;}
    unsigned int get(unsigned int i, unsigned int quantity);
    void sort_by_value();
    bool min_change(unsigned int const &value, std::vector<Currency> &change);
    friend std::ostream & operator << (std::ostream &stream, Cash const &c);
  private:
    std::vector<Currency> _cash;
  };
}

#endif
