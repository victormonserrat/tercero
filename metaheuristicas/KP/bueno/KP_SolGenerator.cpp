#include "KP_SolGenerator.hpp"
#include "KP_Solution.hpp"

#include <cstdlib>
#include <vector>

/*GUARRO*/
#include <iostream>
/*GUARRO*/

KP::SolGenerator::SolGenerator( KP::Solution const &solution ) {
  _solution = solution;
}

std::vector<KP::Solution> KP::SolGenerator::generate( unsigned int const &n ) {
  std::vector<KP::Solution> solutions;

  while( solutions.size() < n ) {
    KP::Solution solution = _solution;
    unsigned int i = rand() % solution.objects().size();
    unsigned int j = rand() % solution.objects().size();
    if(
    ( solution.objects()[i] and not ( solution.objects()[j] ) ) or
    ( not ( solution.objects()[i] ) and solution.objects()[j] )
    ) {
      bool aux = solution.objects()[j];
      solution.object(j, solution.objects()[i]);
      solution.object(i, aux);

      unsigned int weight = 0;
      for( size_t i = 0; i < solution.problem().objects().size(); i++ ) {
        if ( solution.objects()[i] ) {
          weight += solution.problem().objects()[i].weight();
        }
      }
      if ( weight <= solution.problem().knacksack().capacity() ) {
        solutions.push_back( solution );
      }
    }
  }

  return solutions;
}
