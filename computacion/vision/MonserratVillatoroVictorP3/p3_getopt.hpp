#ifndef __P3_GETOPT_HPP__
#define __P3_GETOPT_HPP__

namespace p3{
  void help();
  void assign(int argc, char *argv[], bool &iflag, bool &vflag, bool &sflag, int &svalue, bool &rflag, float &rvalue, bool &nflag, int &nvalue, bool &gflag, float &gvalue, bool &inflag, std::string &invalue, bool &outflag, std::string &outvalue, bool &maskflag, std::string &maskvalue);
  bool getoptions(int argc, char *argv[], bool &iflag, bool &vflag, bool &sflag, int &svalue, bool &rflag, float &rvalue, bool &nflag, int &nvalue, bool &gflag, float &gvalue, bool &inflag, std::string &invalue, bool &outflag, std::string &outvalue, bool &maskflag, std::string &maskvalue);
}

#endif
