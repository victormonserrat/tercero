#include <cstdlib>
#include <ctime>

#include "game.hpp"

#define NBALLS 90

Game::Game(std::vector<User> users){
  srand(time(NULL));
  _users = users;
  for(int i = 0; i < NBALLS; i++){
    _cage.push_back(i+1);
  }
  _state = 0;
}
int Game::number(){
  int number = -1;
  if(_cage.size() > 0){
    int i = rand() % _cage.size();
    number = _cage[i];
    _cage.erase(_cage.begin()+i);
  }
  return number;
}
bool Game::has_cage(int const &number){
  for(int i = 0; i < _cage.size(); i++){
    if(number == _cage[i]){
      return true;
    }
  }
  return false;
}
int Game::lines(Card const &card){
  int l = CARD_ROWS;
  for(int i = 0; i < CARD_ROWS; i++){
    for(int j = 0; j < CARD_COLS; j++){
      if(has_cage(card.card()[i][j])){
        l--;
        break;
      }
    }
  }
  return l;
}
