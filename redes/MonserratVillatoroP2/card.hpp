#ifndef __CARD_HPP__
#define __CARD_HPP__

#include <vector>
#include <iostream>

#define CARD_ROWS 3
#define CARD_COLS 9
#define NBALLS 90

class Card{
public:
  Card();
  std::vector<std::vector<unsigned int>> card() const{return _card;}
  void card(std::vector<std::vector<unsigned int>> &card){_card = card;}
  bool includes(unsigned int const &x);
  friend std::ostream & operator << (std::ostream &stream, Card const &c);
protected:
  void sort_cols();
  void fill();
private:
  std::vector<std::vector<unsigned int>> _card;
};

#endif
