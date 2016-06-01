#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "p6_draught.hpp"

bool is_pushable(int const &row, int const &col, std::vector<p6::Draught> const &draughts){
  for(size_t i = 0; i < draughts.size(); i++){
    if(draughts[i].col() == col or
    std::abs(draughts[i].col() - col) == std::abs(draughts[i].row() - row)){
      return false;
    }
  }
  return true;
}

void draughts(int const &n, std::vector<std::vector<p6::Draught>> &combinations){
  std::vector<p6::Draught> draughts;

  int r = 0;
  int c = 0;
  while(r >= 0){
    if(r == n){
      combinations.push_back(draughts);
      r--;
      c = draughts[r].col() + 1;
      draughts.erase(draughts.begin() + r);
    }
    while(c < n and !is_pushable(r, c, draughts)){
      c++;
    }
    if(c < n){
      draughts.push_back(p6::Draught(r, c));
      r++;
      c = 0;
    }else{
      r--;
      if(r >= 0){
        c = draughts[r].col() + 1;
        draughts.erase(draughts.begin() + r);
      }
    }
  }
}

int main(int argc, char const *argv[]){
  std::cout << "Introduzca el número de reinas (N) para un tablero NxN: ";
  int n;
  std::cin >> n;
  std::vector<std::vector<p6::Draught>> combinations;
  draughts(n, combinations);
  std::cout << "Hay " << combinations.size() << " posibles combinaciones para su colocación, ¿desea verlas? [S/N]: ";
  char c;
  std::cin >> c;
  if(c == 's' or c == 'S'){
    for(size_t i = 0; i < combinations.size(); i++){
      for(size_t j = 0; j < combinations[i].size(); j++){
        std::cout << "(" << combinations[i][j].row() << "," << combinations[i][j].col() << ") ";
      }
      std::cout << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
