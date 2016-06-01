#ifndef __P5_GETOPT_HPP__
#define __P5_GETOPT_HPP__

#include <string>

namespace p5{
  void help();
  void assign(int argc, char *argv[], bool &oflag, std::string &ovalue, bool &nflag, int &nvalue, bool &iflag, std::string &ivalue);
  bool getoptions(int argc, char *argv[], bool &oflag, std::string &ovalue, bool &nflag, int &nvalue, bool &iflag, std::string &ivalue);
}

#endif
