#ifndef __P2_GETOPT_HPP__
#define __P2_GETOPT_HPP__

namespace p2{
  void help();
  void assign(int argc, char *argv[], bool &rflag, unsigned int &rvalue, bool &bflag, bool &sflag, unsigned int &svalue, bool &iflag, std::string &input, bool &oflag, std::string &output, bool &mflag, std::string &mask);
  bool getoptions(int argc, char *argv[], bool &rflag, unsigned int &rvalue, bool &bflag, bool &sflag, unsigned int &svalue, bool &iflag, std::string &input, bool &oflag, std::string &output, bool &mflag, std::string &mask);
}

#endif
