#include "KP_Solution.hpp"
#include "KP_Problem.hpp"

#include <vector>
#include <cstdlib>
#include <algorithm>

KP::Solution::Solution( KP::Problem const &problem )
{
  _problem = problem;
  for( size_t i = 0; i < problem.objects().size(); i++ )
  {
    _objects.push_back( false );
  }

  unsigned int weight = 0;
  unsigned int position;
  std::vector<unsigned int> positions;
  std::vector<unsigned int>::iterator i;
  while( not ( positions.size() ==  problem.objects().size() ) ) {
    position = rand() % problem.objects().size();
    i = std::find( positions.begin(), positions.end(), position );
    if( i == positions.end() ) {
      if( problem.objects()[position].weight() + weight <= problem.knacksack().capacity() ) {
        weight += problem.objects()[position].weight();
        _objects[position] = true;
      }
      positions.push_back( position );
    }
  }
}

KP::Problem KP::Solution::problem() const {
  return _problem;
}

void KP::Solution::problem(KP::Problem const &problem){
  _problem = problem;
}

std::vector<bool> KP::Solution::objects() const {
  return _objects;
}

void KP::Solution::objects(std::vector<bool> const &objects){
  _objects = objects;
}

void KP::Solution::object(int const &position, bool const &data){
  _objects[position] = data;
}
