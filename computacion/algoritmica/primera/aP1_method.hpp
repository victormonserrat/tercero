#ifndef __AP1_METHOD_HPP__
#define __AP1_METHOD_HPP__

#include <vector>
#include <cassert>

namespace aP1{
  class Method{
  public:
    Method(std::vector<unsigned int> const &v){
      assert(!v.empty());
      _v = v;
    }
    ~Method(){}
    std::vector<unsigned int> const &v() const{return _v;}
    void v(std::vector<unsigned int> const &v){_v = v;}
    virtual void sort() = 0;
  protected:
    std::vector<unsigned int> _v;
  };
}

#endif
