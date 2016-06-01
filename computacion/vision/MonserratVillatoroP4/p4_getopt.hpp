#ifndef __P4_GETOPT_HPP__
#define __P4_GETOPT_HPP__

#include <string>

namespace p4{
  void help();
  void assign(int argc, char *argv[], bool &tflag, int &tvalue, bool &iflag, std::string &ivalue, bool &oflag, std::string &ovalue);
  bool getoptions(int argc, char *argv[], bool &tflag, int &tvalue, bool &iflag, std::string &ivalue, bool &oflag, std::string &ovalue);
}

#endif
