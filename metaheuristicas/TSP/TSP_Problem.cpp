#include "TSP_Problem.hpp"
#include "TSP_Node.hpp"

#include <vector>

TSP::Problem::Problem( std::vector<TSP::Node> const &nodes ) {
  _nodes = nodes;
}

std::vector<TSP::Node> TSP::Problem::nodes() const {
  return _nodes;
}

void TSP::Problem::nodes (std::vector <TSP::Node> nodes){
  _nodes = nodes;
}//BORRAR. Es para main inicial
