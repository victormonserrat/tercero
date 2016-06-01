#include <cstdlib>
#include <ctime>
#include <iostream>

#include "card.hpp"

Card::Card(){
  srand(time(NULL));
  std::vector<unsigned int> aux(CARD_COLS);
  for(int i = 0; i < CARD_ROWS; i++){
    _card.push_back(aux);
  }
  fill();
}
void Card::fill(){
  unsigned int n = 0;
  while(n < 15){
    unsigned int x = rand() % NBALLS + 1;
    if(!includes(x)){
      if(x == NBALLS){
        if(_card[n/5][(x-1)/10] == 0){
          _card[n/5][(x-1)/10] = x;
          n++;
        }
      }else{
        if(_card[n/5][x/10] == 0){
          _card[n/5][x/10] = x;
          n++;
        }
      }
    }
  }
  sort_cols();
}
bool Card::includes(unsigned int const &x){
  for(int i = 0; i < CARD_ROWS; i++){
    for(int j = 0; j < CARD_COLS; j++){
      if(x == _card[i][j]){
        return true;
      }
    }
  }
  return false;
}
void Card::sort_cols(){
  for(int i = 0; i < CARD_COLS; i++){
    for(int j = CARD_ROWS - 1; j >= 0; j--){
      if(_card[j][i] != 0){
        unsigned int max = _card[j][i];
        unsigned int max_row = j;
        for(int k = j-1; k >= 0; k--){
          if(_card[k][i] > max){
            max = _card[k][i];
            max_row = k;
          }
        }
        unsigned int aux = _card[j][i];
        _card[j][i] = max;
        _card[max_row][i] = aux;
      }
    }
  }
}
std::ostream & operator << (std::ostream &stream, Card const &c){
  for(int i = 0; i < CARD_ROWS; i++){
    for(int j = 0; j < CARD_COLS; j++){
      if(j == 0){
        stream << "|";
      }
      if(c.card()[i][j] == 0){
          stream << "  |";
      }else{
        if(j == 0){
          stream << " ";
        }
        stream << c.card()[i][j] << "|";
      }
    }
    stream << std::endl;
  }
  return stream;
}
