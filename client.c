#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netdb.h>

int main() {

  struct sockaddr_in cliaddr;

  char sendline[100];
  char recvline[100];
  char str[100];
  int PORT = 7777;

  bzero(&cliaddr, sizeof(cliaddr));

  cliaddr.sin_family = AF_INET;
  cliaddr.sin_addr.s_addr = htons(INADDR_ANY);
  cliaddr.sin_port = htons(PORT);

  int clisocket = socket(AF_INET, SOCK_STREAM, 0);
  int connection = connect(clisocket, (struct sockaddr *) &cliaddr, sizeof(cliaddr));

  if (connection == 0) {
    printf("Connected to server\n");
    write(clisocket, "Hello\n", sizeof(char)*5);

    while(1) {
      read(connection, str, 100);
      printf("%s\n", str);
    }

  }

  /*
  while(1) {
    bzero(sendline, 100);
    bzero(recvline, 100);
    fgets(sendline,100,stdin);

    write(connection, sendline, strlen(sendline)+1);
    read(connection, recvline, 100);
    printf("%s\n", recvline);
  }
  */


}
