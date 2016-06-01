#include "TSP_Node.hpp"

TSP::Node::Node( double const &x, double const &y ) {
  _x = x;
  _y = y;
}

double TSP::Node::x() const {
  return _x;
}

double TSP::Node::y() const {
  return _y;
}
