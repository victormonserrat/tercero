#include <vector>
#include <cassert>
#include <cstdint>

#include "aP1_timing.hpp"
#include "aP1_vector.hpp"
#include "aP1_error.hpp"
#include "aP1_bubble.hpp"
#include "aP1_heap.hpp"
#include "time.hpp"

void aP1::timing(unsigned int const &nMin, unsigned int const &nMax, unsigned int const &inc, unsigned int const &nRep, std::vector<double> &nEle, std::vector<double> &timesB, std::vector<double> &timesH){
  assert(nEle.empty());
  assert(timesB.empty());
  assert(timesH.empty());
  for(size_t i = nMin; i <= nMax; i += inc){
    uint64_t timeB = 0;
    uint64_t timeH = 0;
    for(size_t j = 0; j < nRep; j++){
      std::vector<unsigned int> v;
      aP1::fillVector(v, i);
      aP1::Bubble b(v);
      aP1::Heap h(v);
      Clock c;
      c.start();
      b.sort();
      c.stop();
      timeB += c.elapsed();
      assert(aP1::isSorted(b.v()));
      c.start();
      h.sort();
      c.stop();
      timeH += c.elapsed();
      assert(aP1::isSorted(h.v()));
    }
    nEle.push_back((double)i);
    timesB.push_back((double)timeB/(double)nRep);
    timesH.push_back((double)timeH/(double)nRep);
  }
}
