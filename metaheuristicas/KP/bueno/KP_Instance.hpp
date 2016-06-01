#ifndef __KP_INSTANCE_HPP__
#define __KP_INSTANCE_HPP__

#include "KP_Problem.hpp"
#include "KP_Solution.hpp"

#include <string>
#include <vector>
#include <fstream>

namespace KP {
  class Instance {
    public:
      Instance( std::string const &fileName );
      Instance() {}

      std::vector<KP::Problem> problems() const;

      unsigned long long int profit( KP::Solution const &solution ) const;

    protected:
      std::vector<KP::Object> read_objects(
        std::ifstream      &file,
        unsigned int const &n
      );

    private:
      std::vector<KP::Problem> _problems;
  };
}

#endif
