#ifndef __TSP_PROBLEM_HPP__
#define __TSP_PROBLEM_HPP__

#include "TSP_Node.hpp"

#include <vector>

namespace TSP {
  class Problem {
    public:
      Problem() {}
      Problem( std::vector<TSP::Node> const &nodes );

      std::vector<TSP::Node> nodes() const;

      void nodes (std::vector <TSP::Node> nodes); //BORRAR. Es para main inicial  

    private:
      std::vector<TSP::Node> _nodes;
  };
}

#endif
