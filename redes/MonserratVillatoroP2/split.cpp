#include <string>
#include <vector>

#include "split.hpp"

#define MSG_SIZE 250

std::vector<std::string> split(std::string const &s, std::string const &chars){
  std::string aux = s;
  std::vector<std::string> splitted;
  while(aux.find(chars) <= MSG_SIZE){
    splitted.push_back(aux.substr(0, aux.find(chars)));
    aux.erase(0, aux.find(chars)+1);
  }
  splitted.push_back(aux.substr(0, aux.size()-1));
  return splitted;
}
