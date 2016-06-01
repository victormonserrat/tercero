#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include "rP1_time.h"

#define PORT 2000
#define BUFFER_SIZE 50

int main(int argc, char const *argv[]){
  int sd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sd == -1){
    perror("Socket error\n");
    return -1;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1){
    perror("Bind error\n");
    close(sd);
    return -1;
  }

  struct sockaddr_in client;
  socklen_t client_size = sizeof(client);
  char buffer[BUFFER_SIZE];
  while(1){
    if(recvfrom(sd, &buffer, sizeof(buffer), 0, (struct sockaddr *) &client, &client_size) > 0){
      if((strcmp(buffer, "DAY")) == 0){
        getTime(1, buffer);
      }else if((strcmp(buffer, "TIME")) == 0){
        getTime(2, buffer);
      }
      else if((strcmp(buffer, "DAYTIME")) == 0){
        getTime(3, buffer);
      }
      else{
				sprintf(buffer, "SYNTAX ERROR");
			}
      sendto(sd, &buffer, sizeof(buffer), 0, (struct sockaddr *) &client, client_size);
    }
  }
  close(sd);

  return 0;
}
