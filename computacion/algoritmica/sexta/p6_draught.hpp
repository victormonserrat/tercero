#ifndef __P6_DRAUGHT_HPP__
#define __P6_DRAUGHT_HPP__

namespace p6{
  class Draught{
  public:
    Draught(){}
    Draught(int const &row, int const &col);
    int row() const{return _row;}
    void row(int const &row){_row = row;}
    int col() const{return _col;}
    void col(int const &col){_col = col;}
  private:
    int _row;
    int _col;
  };
}

#endif
