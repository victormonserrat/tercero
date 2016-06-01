#include "TSP_Instance.hpp"
#include "TSP_Problem.hpp"
#include "TSP_Solution.hpp"

#include <vector>
#include <fstream>
#include <cassert>

std::vector<TSP::Node> TSP::Instance::read_nodes(
  std::ifstream      &file,
  unsigned int const &n
) {
  std::vector<TSP::Node> nodes;
  unsigned int           number;
  double                 x;
  double                 y;

  for( unsigned int i = 0; i < n; i++ ) {
    file >> number >> x >> y;
    nodes.push_back( TSP::Node( x, y ) );
  }
  return nodes;
}

TSP::Instance::Instance( std::string const &fileName ) {
  std::ifstream file( fileName.c_str() );
  assert( file );

  std::string tmp;
  std::string name;
  while( file >> tmp >> name ) {
    file >> tmp >> tmp; /* Read "TYPE: type" */

    std::getline( file, tmp, '\n' );
    std::getline( file, tmp, '\n' ); /* Read "COMMENT: Comment" */
    unsigned int n;
    file >> tmp >> n;

    file >> tmp >> tmp; /* Read "EDGE_WEIGHT_TYPE: EdgeWeightType" */
    file >> tmp; /* Read NODE_COORD_SECTION" */

    _problems.push_back( TSP::Problem( read_nodes( file, n ) ) );

    file >> tmp; /* Read "EOF" */
  }
  file.close();
}

std::vector<TSP::Problem> TSP::Instance::problems() const {
  return _problems;
}

double TSP::Instance::distance( TSP::Solution const &solution ) const {
  double distance = 0;
  for( size_t i = 0; i < solution.distances().size(); i++ ) {
    distance += solution.distances()[i];
  }
  return distance;
}
