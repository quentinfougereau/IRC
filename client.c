#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_add
#include <unistd.h>
#include <poll.h>

const char * userName = NULL;

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;

    char server_reply[2000];

    if(argc < 1){
      printf("Default Name set to Anonymous");
      userName = "Anonymous";
    }
    if(argc == 3)
    {
      userName = argv[3];
    }

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 5000 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    //keep communicating with server

    while(1)
    {
       int find = 0;
       char * message = malloc (sizeof (*message) * 256);

	     struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };


       if( poll(&mypoll, 1, 5000) )
       {
         scanf("%s" , message);
         find = 1;
       }

       if(find == 1)
        {
          //Send some data
          if( send(sock , message , strlen(message) , 0) < 0)
          {
              puts("Send failed");
              return 1;
          }
          free(message);
        }

        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }

        puts("Server reply :");
        puts(server_reply);

    }

    close(sock);
    return 0;
}
