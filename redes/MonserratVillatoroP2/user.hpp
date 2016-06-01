#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>

#include "card.hpp"

class User{
public:
  User(){}
  User(int sd){_sd = sd; _state = -1;}
  int sd() const{return _sd;}
  void sd(int const &sd){_sd = sd;}
  std::string name() const{return _name;}
  void name(std::string const &name){_name = name;}
  std::string password() const{return _password;}
  void password(std::string const &password){_password = password;}
  Card card() const{return _card;}
  void card(Card const &card){_card = card;}
  int state() const{return _state;}
  void state(int const &state){_state = state;}
private:
  int _sd;
  std::string _name;
  std::string _password;
  Card _card;
  int _state;
};

#endif
