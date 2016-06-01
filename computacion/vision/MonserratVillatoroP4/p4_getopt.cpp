#include <string>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "p4_getopt.hpp"

void p4::help(){

}
void p4::assign(int argc, char *argv[], bool &tflag, int &tvalue, bool &iflag, std::string &ivalue, bool &oflag, std::string &ovalue){
  for(int i = 1; i < argc; i++){
    if(argv[i][0] == '-'){
      if(argv[i][1] == 't'){
        i++;
      }
    }else{
      if(!iflag){
        ivalue = argv[i];
        iflag = true;
      }else if(!oflag){
        ovalue = argv[i];
        oflag = true;
      }
    }
  }
}
bool p4::getoptions(int argc, char *argv[], bool &tflag, int &tvalue, bool &iflag, std::string &ivalue, bool &oflag, std::string &ovalue){
  int c;
  while((c = getopt(argc, argv, "t:")) != -1){
    switch(c){
      case 'h':
        p4::help();
        abort();
      case 't':
        tflag = true;
        tvalue = atoi(optarg);
        break;
      case '?':
        if(optopt == 't'){
          fprintf(stderr, "%s: -%c <int>\n", argv[0], optopt);
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
  if(tflag){
    i += 2;
  }
  if(argc - i == 2){
    p4::assign(argc, argv, tflag, tvalue, iflag, ivalue, oflag, ovalue);
  }else{
    std::cout << "Error de sintaxis. Debe especificar un video de entrada y otro de salida. Use la opción -h para ver la ayuda" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
