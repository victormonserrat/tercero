#ifndef __TSP_NODE_HPP__
#define __TSP_NODE_HPP__

namespace TSP {
  class Node {
    public:
      Node (){}
      Node( double const &x, double const &y );

      double x() const;
      double y() const;

    private:
      double _x;
      double _y;
  };
}

#endif
