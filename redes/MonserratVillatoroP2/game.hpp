#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <vector>
#include <cstdlib>
#include <ctime>

#include "user.hpp"
#include "card.hpp"

#define NBALLS 90

class Game{
public:
  Game(){_state = 0;}
  Game(std::vector<User> users);
  std::vector<User> users() const{return _users;}
  void users(std::vector<User> users){_users = users;}
  int state() const{return _state;}
  void state(int const &state){_state = state;}
  int number();
  bool has_cage(int const &number);
  int lines(Card const &card);
private:
  std::vector<User> _users;
  std::vector<unsigned int> _cage;
  int _state;
};

#endif
