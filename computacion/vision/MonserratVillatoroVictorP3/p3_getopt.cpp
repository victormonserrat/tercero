#include <string>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "p3_getopt.hpp"

void p3::help(){

}

void p3::assign(int argc, char *argv[], bool &iflag, bool &vflag, bool &sflag, int &svalue, bool &rflag, float &rvalue, bool &nflag, int &nvalue, bool &gflag, float &gvalue, bool &inflag, std::string &invalue, bool &outflag, std::string &outvalue, bool &maskflag, std::string &maskvalue){
  for(int i = 1; i < argc; i++){
    if(argv[i][0] == '-'){
      if(argv[i][1] == 's' or argv[i][1] == 'n'){
        i++;
      }else if(argv[i][1] == 'r' or argv[i][1] == 'g'){
        i++;
      }
    }else{
      if(!inflag){
        invalue = argv[i];
        inflag = true;
      }else if(!outflag){
        outvalue = argv[i];
        outflag = true;
      }else{
        maskvalue = argv[i];
        maskflag = true;
      }
    }
  }
}

bool p3::getoptions(int argc, char *argv[], bool &iflag, bool &vflag, bool &sflag, int &svalue, bool &rflag, float &rvalue, bool &nflag, int &nvalue, bool &gflag, float &gvalue, bool &inflag, std::string &invalue, bool &outflag, std::string &outvalue, bool &maskflag, std::string &maskvalue){
  int c;
  while((c = getopt(argc, argv, "hivs:r:n:g:")) != -1){
    switch(c){
      case 'h':
        help();
        return EXIT_FAILURE;
      case 'i':
        iflag = true;
        break;
      case 'v':
        vflag = true;
        break;
      case 's':
        sflag = true;
        svalue = atoi(optarg);
        break;
      case 'r':
        rflag = true;
        rvalue = atof(optarg);
        break;
      case 'n':
        nflag = true;
        nvalue = atoi(optarg);
        break;
      case 'g':
        gflag = true;
        gvalue = atof(optarg);
        break;
      case '?':
        if(optopt == 's'){
          fprintf(stderr, "%s: -%c <int>\n", argv[0], optopt);
        }else if(optopt == 'r'){
          fprintf(stderr, "%s: -%c <float>\n", argv[0], optopt);
        }else if(optopt == 'n'){
          fprintf(stderr, "%s: -%c <int>\n", argv[0], optopt);
        }else if(optopt == 'g'){
          fprintf(stderr, "%s: -%c <float>\n", argv[0], optopt);
        }else if(isprint(optopt)){
          std::cout << stderr << std::endl;
        }else{
          std::cout << stderr << std::endl;
        }
        return EXIT_FAILURE;
      default:
        abort();
    }
  }
  unsigned int i = 1;
  if(iflag){
    i++;
  }
  if(vflag){
    i++;
  }
  if(sflag){
    i += 2;
  }
  if(rflag){
    i += 2;
  }
  if(nflag){
    i += 2;
  }
  if(gflag){
    i += 2;
  }
  if(argc - i > 1 and argc - i < 4){
    p3::assign(argc, argv, iflag, vflag, sflag, svalue, rflag, rvalue, nflag, nvalue, gflag, gvalue, inflag, invalue, outflag, outvalue, maskflag, maskvalue);
  }else{
    std::cout << "Error de sintaxis. Debe especificar una imagen de entrada y otra de salida al menos. Use la opción -h para ver la ayuda" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
