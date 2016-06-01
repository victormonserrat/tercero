#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <vector>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include "user.hpp"
#include "game.hpp"
#include "split.hpp"

#define MSG_SIZE 250
#define MAX_USERS 40
#define MAX_GAMES 10
#define USERS_PER_GAME 4
#define CAGE_TIMEOUT 5

std::vector<Game> games;
char buffer[MSG_SIZE];

void sigint(int signum){
  std::cout << "Para salir escriba SALIR." << std::endl;
}

void turn(int signum){
  for(int i = 0; i < games.size(); i++){
    bzero(buffer, sizeof(buffer));
    std::string aux_buffer = "NUMERO-OBTENIDO ";
    aux_buffer += std::to_string(games[i].number());
    strcpy(buffer, aux_buffer.c_str());
    for(int j = 0; j < games[i].users().size(); j++){
      send(games[i].users()[j].sd(), buffer, strlen(buffer), 0);
    }
  }
  alarm(CAGE_TIMEOUT);
}

int main(int argc, char const *argv[]){
  int sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd == -1){
    perror("Socket error\n");
  }
  int on = 1;
  int ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  struct sockaddr_in sockname;
  sockname.sin_family = AF_INET;
  sockname.sin_port = htons(2050);
  sockname.sin_addr.s_addr = INADDR_ANY;

  if(bind(sd, (struct sockaddr *) &sockname, sizeof(sockname)) == -1){
    perror("Bind error\n");
    return EXIT_FAILURE;
  }

  if(listen(sd, 1) == -1){
    perror("Listen error\n");
    return EXIT_FAILURE;
  }

  fd_set readfds, auxfds;
  FD_ZERO(&readfds);
  FD_ZERO(&auxfds);
  FD_SET(sd, &readfds);
  FD_SET(0, &readfds);

  std::signal(SIGINT, sigint);

  std::signal(SIGALRM, turn);
  alarm(CAGE_TIMEOUT);

  struct sockaddr_in from;
  socklen_t from_len = sizeof(from);
  std::vector<User> users;
  std::vector<User> queue;
  int new_sd;
  while(true){
    auxfds = readfds;
    if(select(FD_SETSIZE, &auxfds, NULL, NULL, NULL) > 0){
      for(int i = 0; i < FD_SETSIZE; i++){
        if(FD_ISSET(i, &auxfds)){
          if(i == sd){
            if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
              perror("Accept error\n");
            }else{
              if(users.size() < MAX_USERS){
                users.push_back(User(new_sd));
                FD_SET(new_sd, &readfds);
                bzero(buffer, sizeof(buffer));
                strcpy(buffer, "+OK. Usuario conectado");
                send(new_sd, buffer, strlen(buffer), 0);
              }else{
                bzero(buffer, sizeof(buffer));
                strcpy(buffer, "-ERR. Demasiados usuarios conectados simultáneamente");
                send(new_sd, buffer, strlen(buffer), 0);
                close(new_sd);
              }
            }
          }else if(i == 0){
            bzero(buffer, sizeof(buffer));
            fgets(buffer, sizeof(buffer), stdin);
            if(strcmp(buffer, "SALIR\n") == 0){
              bzero(buffer, sizeof(buffer));
              strcpy(buffer, "-ERR. Desconexión del servidor");
              for(int j = 0; j < users.size(); j++){
                send(users[j].sd(), buffer, strlen(buffer), 0);
                close(users[j].sd());
                FD_CLR(users[j].sd(), &readfds);
              }
              close(sd);
              return EXIT_SUCCESS;
            }else{
              std::cout << "-ERR. Comando no válido" << std::endl;
            }
          }else{
            bzero(buffer, sizeof(buffer));
            if(recv(i, buffer, sizeof(buffer), 0) > 0){
              std::vector<std::string> splitted_buffer = split(std::string(buffer), " ");
              if(splitted_buffer[0] == "USUARIO"){
                std::ifstream f("users.txt");
                std::string name, password;
                bool is_user = false;
                while(f >> name >> password){
                  if(splitted_buffer[1] == name){
                    for(int j = 0; j < users.size(); j++){
                      if(i == users[j].sd()){
                        is_user = true;
                        users[j].name(name);
                        users[j].password(password);
                        users[j].state(0);
                        break;
                      }
                    }
                  }
                }
                f.close();
                bzero(buffer, sizeof(buffer));
                if(is_user){
                  strcpy(buffer, "+OK. Usuario correcto");
                }else{
                  for(int j = 0; j < users.size(); j++){
                    if(i == users[j].sd()){
                      users[j].state(-1);
                    }
                  }
                  strcpy(buffer, "-ERR. Usuario incorrecto");
                }
                send(i, buffer, strlen(buffer), 0);
              }else if(splitted_buffer[0] == "PASSWORD"){
                bzero(buffer, sizeof(buffer));
                for(int j = 0; j < users.size(); j++){
                  if(i == users[j].sd()){
                    if(users[j].state() >= 0){
                      if(users[j].password() == splitted_buffer[1]){
                        users[j].state(1);
                        strcpy(buffer, "+OK. Usuario validado");
                      }else{
                        users[j].state(0);
                        strcpy(buffer, "-ERR. Error en la validación");
                      }
                    }else{
                      strcpy(buffer, "-ERR. Usuario no introducido");
                    }
                    break;
                  }
                }
                send(i, buffer, strlen(buffer), 0);
              }else if(splitted_buffer[0] == "REGISTRO"){
                bzero(buffer, sizeof(buffer));
                if(splitted_buffer.size() == 5 and
                   splitted_buffer[1] == "-u" and
                   splitted_buffer[3] == "-p"){
                  std::ifstream inf("users.txt");
                  std::string name, password;
                  bool is_user = false;
                  while(inf >> name >> password){
                    if(name == splitted_buffer[2]){
                      is_user = true;
                      break;
                    }
                  }
                  inf.close();
                  if(!is_user){
                    std::ofstream outf("users.txt", std::ios_base::app);
                    for(int j = 0; j < users.size(); j++){
                      if(i == users[j].sd()){
                        users[j].name(splitted_buffer[2]);
                        users[j].password(splitted_buffer[4]);
                        outf << users[j].name() + "\t" + users[j].password() << std::endl;
                        users[j].state(1);
                        strcpy(buffer, "+OK. Usuario registrado");
                        break;
                      }
                    }
                    outf.close();
                  }else{
                    strcpy(buffer, "-ERR. Usuario ya registrado");
                  }
                }else{
                  strcpy(buffer, "-ERR. Error de sintaxis");
                }
                send(i, buffer, strlen(buffer), 0);
              }else if(splitted_buffer[0] == "INICIAR-PARTIDA"){
                bzero(buffer, sizeof(buffer));
                if(games.size() != MAX_GAMES){
                  for(int j = 0; j < users.size(); j++){
                    if(i == users[j].sd()){
                      if(users[j].state() == 1){
                        users[j].state(2);
                        queue.push_back(users[j]);
                        strcpy(buffer, "+OK. Petición recibida. Quedamos a la espera de más jugadores");
                      }else if(users[j].state() == 2){
                        strcpy(buffer, "-ERR. Usuario ya en cola");
                      }else if(users[j].state() == 3){
                        strcpy(buffer, "-ERR. Usuario ya en partida");
                      }else{
                        strcpy(buffer, "-ERR. Usuario no introducido");
                      }
                      break;
                    }
                  }
                }else{
                  strcpy(buffer, "-ERR. Demasiadas partidas simultáneas");
                }
                send(i, buffer, strlen(buffer), 0);
                sleep(2);
                if(queue.size() == USERS_PER_GAME){
                  bzero(buffer, sizeof(buffer));
                  strcpy(buffer, "+OK. Empieza la partida");
                  for(int j = 0; j < queue.size(); j++){
                    send(queue[j].sd(), buffer, strlen(buffer), 0);
                    for(int k = 0; k < users.size(); k++){
                      if(users[k].sd() == queue[j].sd()){
                        users[k].state(3);
                      }
                    }
                    queue[j].state(3);
                  }
                  sleep(2);
                  for(int j = 0; j < queue.size(); j++){
                    bzero(buffer, sizeof(buffer));
                    std::string aux_buffer = "CARTON";
                    Card aux = queue[j].card();
                    for(int r = 0; r < CARD_ROWS; r++){
                      for(int c = 0; c < CARD_COLS; c++){
                        aux_buffer += " ";
                        aux_buffer += std::to_string(aux.card()[r][c]);
                      }
                    }
                    strcpy(buffer, aux_buffer.c_str());
                    send(queue[j].sd(), buffer, strlen(buffer), 0);
                  }
                  sleep(2);
                  Game g(queue);
                  games.push_back(g);
                  std::vector<User> new_queue;
                  queue = new_queue;
                }
              }else if(splitted_buffer[0] == "SALIR-PARTIDA"){
              }else if(splitted_buffer[0] == "UNA-LINEA"){
                User aux_user;
                for(int j = 0; j < users.size(); j++){
                  if(i == users[j].sd()){
                    aux_user = users[j];
                  }
                }
                if(aux_user.state() == 3){
                  Game aux_game;
                  for(int j = 0; j < games.size(); j++){
                    for(int k = 0; k < games[j].users().size(); k++){
                      if(i == games[j].users()[k].sd()){
                        aux_game = games[j];
                        break;
                      }
                    }
                  }
                  if(aux_game.state() < 1 and aux_game.lines(aux_user.card()) >= 1){
                    bzero(buffer, sizeof(buffer));
                    std::string aux_buffer = "+OK. Jugador ";
                    aux_buffer += aux_user.name();
                    aux_buffer += " ha cantado línea";
                    strcpy(buffer, aux_buffer.c_str());
                    for(int j = 0; j < aux_game.users().size(); j++){
                      send(aux_game.users()[j].sd(), buffer, strlen(buffer), 0);
                    }
                    for(int j = 0; j < games.size(); j++){
                      for(int k = 0; k < games[j].users().size(); k++){
                        if(i == games[j].users()[k].sd()){
                          games[j].state(1);
                          break;
                        }
                      }
                    }
                  }else{
                    bzero(buffer, sizeof(buffer));
                    strcpy(buffer, "-ERR. El comando UNA-LINEA no procede");
                    send(aux_user.sd(), buffer, strlen(buffer), 0);
                  }
                }else{
                  bzero(buffer, sizeof(buffer));
                  strcpy(buffer, "-ERR. Usuario sin partida");
                  send(aux_user.sd(), buffer, strlen(buffer), 0);
                }
              }else if(splitted_buffer[0] == "DOS-LINEAS"){
                User aux_user;
                for(int j = 0; j < users.size(); j++){
                  if(i == users[j].sd()){
                    aux_user = users[j];
                  }
                }
                if(aux_user.state() == 3){
                  Game aux_game;
                  for(int j = 0; j < games.size(); j++){
                    for(int k = 0; k < games[j].users().size(); k++){
                      if(i == games[j].users()[k].sd()){
                        aux_game = games[j];
                        break;
                      }
                    }
                  }
                  if(aux_game.state() < 2 and aux_game.lines(aux_user.card()) >= 2){
                    bzero(buffer, sizeof(buffer));
                    std::string aux_buffer = "+OK. Jugador ";
                    aux_buffer += aux_user.name();
                    aux_buffer += " ha cantado dos líneas";
                    strcpy(buffer, aux_buffer.c_str());
                    for(int j = 0; j < aux_game.users().size(); j++){
                      send(aux_game.users()[j].sd(), buffer, strlen(buffer), 0);
                    }
                    for(int j = 0; j < games.size(); j++){
                      for(int k = 0; k < games[j].users().size(); k++){
                        if(i == games[j].users()[k].sd()){
                          games[j].state(2);
                          break;
                        }
                      }
                    }
                  }else{
                    bzero(buffer, sizeof(buffer));
                    strcpy(buffer, "-ERR. El comando DOS-LINEAS no procede");
                    send(aux_user.sd(), buffer, strlen(buffer), 0);
                  }
                }else{
                  bzero(buffer, sizeof(buffer));
                  strcpy(buffer, "-ERR. Usuario sin partida");
                  send(aux_user.sd(), buffer, strlen(buffer), 0);
                }
              }else if(splitted_buffer[0] == "BINGO"){
                User aux_user;
                for(int j = 0; j < users.size(); j++){
                  if(i == users[j].sd()){
                    aux_user = users[j];
                  }
                }
                if(aux_user.state() == 3){
                  Game aux_game;
                  for(int j = 0; j < games.size(); j++){
                    for(int k = 0; k < games[j].users().size(); k++){
                      if(i == games[j].users()[k].sd()){
                        aux_game = games[j];
                        break;
                      }
                    }
                  }
                  if(aux_game.state() < 3 and aux_game.lines(aux_user.card()) >= 3){
                    bzero(buffer, sizeof(buffer));
                    std::string aux_buffer = "+OK. Jugador ";
                    aux_buffer += aux_user.name();
                    aux_buffer += " ha cantado bingo";
                    strcpy(buffer, aux_buffer.c_str());
                    for(int j = 0; j < aux_game.users().size(); j++){
                      send(aux_game.users()[j].sd(), buffer, strlen(buffer), 0);
                    }
                    for(int j = 0; j < games.size(); j++){
                      for(int k = 0; k < games[j].users().size(); k++){
                        if(i == games[j].users()[k].sd()){
                          games[j].state(3);
                          games.erase(games.begin()+j);
                          break;
                        }
                      }
                    }
                    for(int j = 0; j < users.size(); j++){
                      for(int k = 0; k < aux_game.users().size(); k++){
                        if(users[j].sd() == aux_game.users()[k].sd()){
                          users[j].state(1);
                        }
                      }
                    }
                  }else{
                    bzero(buffer, sizeof(buffer));
                    strcpy(buffer, "-ERR. El comando BINGO no procede");
                    send(aux_user.sd(), buffer, strlen(buffer), 0);
                  }
                }else{
                  bzero(buffer, sizeof(buffer));
                  strcpy(buffer, "-ERR. Usuario sin partida");
                  send(aux_user.sd(), buffer, strlen(buffer), 0);
                }
              }else if(splitted_buffer[0] == "SALIR"){
                for(int j = 0; j < users.size(); j++){
                  if(i == users[j].sd()){
                    if(users[j].state() == 2){
                      for(int k = 0; k < queue.size(); k++){
                        if(users[j].sd() == queue[k].sd()){
                          queue.erase(queue.begin()+k);
                          break;
                        }
                      }
                    }else if(users[j].state() == 3){
                      for(int k = 0; k < games.size(); k++){
                        for(int l = 0; l < games[k].users().size(); l++){
                          if(users[j].sd() == games[k].users()[l].sd()){
                            if(games[k].users().size() == 1){
                              games.erase(games.begin()+k);
                            }else{
                              bzero(buffer, sizeof(buffer));
                              std::string aux_buffer = "+OK. Usuario ";
                              aux_buffer += users[j].name();
                              aux_buffer += " ha abandonado la partida";
                              strcpy(buffer, aux_buffer.c_str());
                              for(int m = 0; m < games[k].users().size(); m++){
                                send(games[k].users()[m].sd(), buffer, strlen(buffer), 0);
                              }
                              std::vector<User> game_users = games[k].users();
                              game_users.erase(game_users.begin()+l);
                              games[k].users(game_users);
                            }
                          }
                        }
                      }
                    }
                    users.erase(users.begin()+j);
                    bzero(buffer, sizeof(buffer));
                    strcpy(buffer, "+OK. Desconexión procesada");
                    send(users[j].sd(), buffer, strlen(buffer), 0);
                    break;
                  }
                }
              }else{
                for(int j = 0; j < users.size(); j++){
                  if(i == users[j].sd()){
                    bzero(buffer, sizeof(buffer));
                    strcpy(buffer, "-ERR. Comando no válido");
                    send(users[j].sd(), buffer, strlen(buffer), 0);
                    break;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  close(sd);

  return EXIT_SUCCESS;
}
