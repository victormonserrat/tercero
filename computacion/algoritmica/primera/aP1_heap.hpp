#ifndef __AP1_HEAP_HPP__
#define __AP1_HEAP_HPP__

#include <vector>
#include <algorithm>
#include <cstdlib>

#include "aP1_method.hpp"

namespace aP1{
  class Heap : public Method{
  public:
    Heap(std::vector<unsigned int> const &v) : Method(v){}
    ~Heap(){}
    void sort(){
      /*std::make_heap(_v.begin(), _v.end());
      std::sort_heap(_v.begin(), _v.end());*/
      makeInitialHeap(_v);
      for(size_t i = _v.size() - 1; i > 0; i--){
        swap(_v, i, 0);
        sift(_v, i, 0);
      }
    }
  private:
    void makeInitialHeap(std::vector<unsigned int> &v){
      for(int i = v.size() - 1; i >= 0; i--){
        sift(v, v.size(), i);
      }
    }
    void swap(std::vector<unsigned int> &v, unsigned int const &i, unsigned int const &j){
      if(i == j){
        return;
      }
      unsigned int aux;
      aux = v[i];
      v[i] = v[j];
      v[j] = aux;
    }
    void sift(std::vector<unsigned int> &v, unsigned int const &heapSize, unsigned int const &siftNode){
      unsigned int i, j;
      j = siftNode;
      do{
        i = j;
        if(((2 * i + 1) < heapSize) && v[j] < v[2 * i + 1]){
          j = 2 * i + 1;
        }
        if(((2 * i + 2) < heapSize) && v[j] < v[2 * i + 2]){
          j = 2 * i + 2;
        }
        swap(v, i, j);
      }while(i != j);
    }
  };
}

#endif
