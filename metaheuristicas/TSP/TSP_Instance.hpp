#ifndef __TSP_INSTANCE_HPP__
#define __TSP_INSTANCE_HPP__

#include "TSP_Problem.hpp"
#include "TSP_Solution.hpp"

#include <string>
#include <vector>
#include <fstream>

namespace TSP {
  class Instance {
    public:
      Instance() {}
      Instance( std::string const &fileName );

      std::vector<TSP::Problem> problems() const;

      double distance( TSP::Solution const &solution ) const;

    protected:
      std::vector<TSP::Node> read_nodes(
        std::ifstream &file,
        unsigned int const &n
      );

    private:
      std::vector<TSP::Problem> _problems;
  };
}

#endif
