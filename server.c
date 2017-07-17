#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

/* Client structure */
typedef struct {
	struct sockaddr_in addr;
	int connfd;
	int uid;
	char name[32];
} client_t;

#define LIMIT_CLIENTS	100

client_t *clients[100];



void * connection_handler(void *);
void queue_add(client_t *);



int main(int argc , char *argv[])
{
  int socket_desc , client_sock , c , *new_sock;
      struct sockaddr_in server , client;

      //Create socket
      socket_desc = socket(AF_INET , SOCK_STREAM , 0);
      if (socket_desc == -1)
      {
          printf("Could not create socket");
      }
      puts("Socket created");

      //Prepare the sockaddr_in structure
      server.sin_family = AF_INET;
      server.sin_addr.s_addr = INADDR_ANY;
      server.sin_port = htons( 8888 );

      //Bind
      if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
      {
          //print the error message
          perror("bind failed. Error");
          return 1;
      }
      puts("bind done");

      //Listen
      listen(socket_desc , 3);

      //Accept and incoming connection
      puts("Waiting for incoming connections...");
      c = sizeof(struct sockaddr_in);

      //Accept and incoming connection
      puts("Waiting for incoming connections...");
      c = sizeof(struct sockaddr_in);
      while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
      {
          puts("Connection accepted");


      		client_t *cli = (client_t *)malloc(sizeof(client_t));
      		cli->connfd = client_sock;
          queue_add(cli);

          pthread_t sniffer_thread;
          new_sock = malloc(1);
          *new_sock = client_sock;

          if( pthread_create( &sniffer_thread, NULL ,connection_handler,(void*) new_sock) < 0)
          {
              perror("could not create thread");
              return 1;
          }
          puts("Handler assigned");
      }

      if (client_sock < 0)
      {
          perror("accept failed");
          return 1;
      }

      return 0;
  }

  /* Add client to queue */
  void queue_add(client_t *cl){
  	int i;

    for(i=0;i<LIMIT_CLIENTS;i++){

  		if(!clients[i]){

        clients[i] = cl;
  			return;

      }

  	}

  }

  void * connection_handler(void * socket_desc)
  {
    int sock = *(int *) socket_desc;
    int read_size;
    char *message, client_message[2000];

    //message = "Bienvenue sur notre serveur";
    //write(sock,message ,strlen(message));

    client_message[0] = "/0";

    while((read_size) = recv(sock,client_message,2000,0) > 0 )
    {

      int i;

      for(i=0;i<LIMIT_CLIENTS;i++) {
            if(clients[i]) {
                write(clients[i]->connfd,client_message, strlen(client_message));
            }
      }


      //write(sock,client_message, strlen(client_message));
    }
    if(read_size == 0)
    {
      puts("Deco");
      fflush(stdout);
    }
    else if(read_size == -1)
    {
      perror("recv failed");
    }

    free(socket_desc);
  }
