#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netdb.h>

int main() {

  struct sockaddr_in servaddr;
  char* dataread;
  char str[100];
  int PORT = 7777;

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htons(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  int servsocket = socket(AF_INET, SOCK_STREAM, 0);
  int servbind = bind(servsocket, (struct sockaddr *) &servaddr, sizeof(servaddr));
  int servlisten = listen(servsocket, 1);

  if (servlisten == 0) {
    printf("En attente de connexion d'un client \n");

    int conn = accept(servsocket, NULL, NULL);

    //while (1) {

      if (conn != -1) {
        printf("Client connected : %d\n", conn);
        read(conn, str, 100);
        //printf("Echoing back - %s\n", str);
        write(conn, strcat(str, " => Reponse server"), sizeof(char)*5);
      }

    //}

  } else {
    printf("Error listen() has returned : %d\n", servlisten);
  }


  while(1) {



    /*
    bzero(str, 100);
    read(conn, str, 100);

    printf("Echoing back - %s\n", str);

    write(conn, str, strlen(str)+1);
    */

  }

  /*
  if (conn != -1) {
    printf("Client connected\n");
  }
  */


}
