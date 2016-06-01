#include <vector>
#include <cstdlib>
#include <cassert>
#include <cstdint>

#include "aP2_timing.hpp"
#include "matriz.hpp"
#include "aP2_matrix.hpp"
#include "time.hpp"
#include "aP2_det.hpp"

void aP2::timing(unsigned int const &nMin, unsigned int const &nMax, unsigned int const &inc, unsigned int const &nRep, std::vector<double> &nEle, double const &min, double const &max, std::vector<double> &timesI, std::vector<double> &timesR){
  assert(nEle.empty());
  assert(timesI.empty());
  assert(timesR.empty());
  for(size_t i = nMin; i <= nMax; i+= inc){
    uint64_t timeI = 0;
    uint64_t timeR = 0;
    for(size_t j = 0; j < nRep; j++){
      Matriz<double> m(i, i);
      aP2::fill(m, min, max);
      Clock c;
      c.start();
      determinanteIterativo(m);
      c.stop();
      timeI += c.elapsed();
      c.start();
      determinanteRecursivo(m);
      c.stop();
      timeR += c.elapsed();
    }
    nEle.push_back(i);
    timesI.push_back((double)timeI/(double)nRep);
    timesR.push_back((double)timeR/(double)nRep);
  }
}
