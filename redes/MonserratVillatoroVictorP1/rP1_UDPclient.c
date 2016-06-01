#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define PORT 2000
#define BUFFER_SIZE 50
#define CONNECTION_ATTEMPTS_LIMIT 3

int main(int argc, char const *argv[]){
  int cd = socket(AF_INET, SOCK_DGRAM, 0);
  if(cd == -1){
    perror("Socket error\n");
    return -1;
  }

  printf("1 -   DAY   - 1\n");
  printf("2 -   TIME  - 2\n");
  printf("3 - DAYTIME - 3\n");
  printf("Choose: ");
  int choice;
  scanf("%i", &choice);

  char buffer[BUFFER_SIZE];
  switch(choice){
    case 1:
      strcpy(buffer, "DAY");
      break;
    case 2:
      strcpy(buffer, "TIME");
      break;
    case 3:
      strcpy(buffer, "DAYTIME");
      break;
  }

  struct sockaddr_in server;
  socklen_t server_size = sizeof(server);
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = inet_addr(argv[1]);

  int i;
  for(i = 0; i < CONNECTION_ATTEMPTS_LIMIT; i++){
    fd_set readset;
    FD_ZERO(&readset);
    FD_SET(cd, &readset);

    struct timeval timeout;
    timeout.tv_sec = atoi(argv[2]);
    timeout.tv_usec = 0;

    if(sendto(cd, &buffer, sizeof(buffer), 0, (struct sockaddr *) &server, server_size) < 0){
      perror("Sendto error\n");
      close(cd);
      return -1;
    }else{
      int result = select(cd+1, &readset, NULL, NULL, &timeout);
      if(result == -1){
        perror("Select error\n");
        close(cd);
        return -1;
      }else if(result == 0){
        printf("Request time out\n");
        fflush(stdout);
      }else{
        if(recvfrom(cd, &buffer, sizeof(buffer), 0, (struct sockaddr *) &server, &server_size) > 0){
          printf("%s\n", buffer);
          close(cd);
          return 0;
        }else{
          perror("Recvfrom error\n");
          close(cd);
          return -1;
        }
      }
    }
  }
  printf("Attempted connections exceeded\n");
  close(cd);
  return -1;
}
