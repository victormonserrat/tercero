#ifndef __AP1_BUBBLE_HPP__
#define __AP1_BUBBLE_HPP__

#include <vector>
#include <cstdlib>

#include "aP1_method.hpp"

namespace aP1{
  class Bubble : public Method{
  public:
    Bubble(std::vector<unsigned int> const &v) : Method(v){}
    ~Bubble(){}
    void sort(){
      for(size_t i = 1; i < _v.size(); i++){
        for(size_t j = 0; j < _v.size()-i; j++){
          if(_v[j] > _v[j+1]){
            unsigned int aux = _v[j];
            _v[j] = _v[j+1];
            _v[j+1] = aux;
          }
        }
      }
    }
  };
}

#endif
