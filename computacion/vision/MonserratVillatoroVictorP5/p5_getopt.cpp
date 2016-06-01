#include <string>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "p5_getopt.hpp"

void p5::help(){

}
void p5::assign(int argc, char *argv[], bool &oflag, std::string &ovalue, bool &nflag, int &nvalue, bool &iflag, std::string &ivalue){
  for(int i = 1; i < argc; i++){
    if(argv[i][0] == '-'){
      if(argv[i][1] == 'o' ){
        i++;
      }else if(argv[i][1] == 'n' ){
        i++;
      }
    }else{
        ivalue = argv[i];
        iflag = true;
    }
  }
}
bool p5::getoptions(int argc, char *argv[], bool &oflag, std::string &ovalue, bool &nflag, int &nvalue, bool &iflag, std::string &ivalue){
  int c;
  while((c = getopt(argc, argv, "o:n:")) != -1){
    switch(c){
      case 'h':
        p5::help();
        abort();
      case 'o':
        oflag = true;
        ovalue = optarg;
        break;
      case 'n':
        nflag = true;
        nvalue = atoi(optarg);
        break;
      case '?':
        if(optopt == 'o'){
          fprintf(stderr, "%s: -%c <.txt>\n", argv[0], optopt);
        }else if(optopt == 'n'){
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
  if(oflag){
    i += 2;
  }
  if(nflag){
    i += 2;
  }
  if(argc - i == 1){
    p5::assign(argc, argv, oflag, ovalue, nflag, nvalue, iflag, ivalue);
  }else{
    std::cout << "Error de sintaxis. Debe especificar una imagen de entrada. Use la opción -h para ver la ayuda" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
