#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <csignal>
#include <vector>
#include <string>

#include "split.hpp"
#include "card.hpp"

#define INET_ADDR "127.0.0.1"
#define MSG_SIZE 250

int sd;
char buffer[MSG_SIZE];

void sigint(int signum){
  std::cout << "Para salir escriba SALIR." << std::endl;
  bzero(buffer, sizeof(buffer));
  send(sd, buffer, sizeof(buffer), 0);
}

int main(int argc, char const *argv[]){
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd == -1){
    perror("Socket error\n");
    return EXIT_FAILURE;
  }
  struct sockaddr_in sockname;
  sockname.sin_family = AF_INET;
  sockname.sin_port = htons(2050);
  sockname.sin_addr.s_addr = inet_addr(INET_ADDR);

  socklen_t len_sockname = sizeof(sockname);
  if(connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1){
    perror("Connect error\n");
    return EXIT_FAILURE;
  }

  fd_set readfds, auxfds;
  FD_ZERO(&auxfds);
  FD_ZERO(&readfds);
  FD_SET(0, &readfds);
  FD_SET(sd, &readfds);

  std::signal(SIGINT, sigint);

  while(true){
    auxfds = readfds;
    select(sd + 1, &auxfds, NULL, NULL, NULL);

    if(FD_ISSET(sd, &auxfds)){
      bzero(buffer, sizeof(buffer));
      recv(sd, buffer, sizeof(buffer), 0);
      std::vector<std::string> splitted_buffer = split(std::string(buffer), " ");
      if(splitted_buffer[0] == "CARTON"){
        Card c;
        std::vector<std::vector<unsigned int>> card = c.card();
        for(int i = 0; i < CARD_ROWS; i++){
          for(int j = 0; j < CARD_COLS; j++){
            card[i][j] = atoi((splitted_buffer[i*CARD_COLS+j+1]).c_str());
          }
        }
        c.card(card);
        std::cout << std::endl << c << std::endl;
      }else{
        std::cout << buffer << std::endl;
      }
      if(strcmp(buffer, "+OK. Desconexión procesada") == 0){
        break;
      }
      if(strcmp(buffer, "-ERR. Desconexión del servidor") == 0){
        break;
      }
      if(strcmp(buffer, "-ERR. Demasiados usuarios conectados simultáneamente") == 0){
        break;
      }
    }else{
      if(FD_ISSET(0, &auxfds)){
        bzero(buffer, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);
        send(sd, buffer, sizeof(buffer), 0);
      }
    }
  }

  close(sd);

  return EXIT_SUCCESS;
}
