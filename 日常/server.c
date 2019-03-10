#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main()
{
  int server_sock = -1;
  u_short port = 8080;

  int client_sock = -1;
  struct sockaddr_in client_name;
  socklen_t client_name_len = sizeof(client_name);
  
  struct sockaddr_in name;
  server_sock = socket(PF_INET, SOCK_STREAM, 0);
  if(server_sock == -1)
  {
    printf("socket failed");
    exit(1);
  }
  memset(&name, 0, sizeof(name));
  name.sin_family = AF_INET;
  name.sin_port = htons(port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);

  int on = 1;

  if((setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
  {
    printf("setsockopt failed");
    exit(1);
  }
  
  if(bind(server_sock, (struct sockaddr *)&name, sizeof(name)) < 0)
  {
    printf("bind failed");
    exit(1);
  }

  if (listen(server_sock, 5) < 0)
  {
    printf("listen, failed");
    exit(1);
  }

  printf("httpd running...\n");

  client_sock = accept(server_sock, (struct sockaddr *)&client_name, &client_name_len);
  if(client_sock == -1)
  {
    printf("accept failed\n");
    exit(1);
  }

  printf("ip:");
  printf("%s", inet_ntoa(client_name.sin_addr));
  printf(" : ");
  printf("%u", ntohs(client_name.sin_port));
  printf("\n");

  return 0;
}
