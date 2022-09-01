#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Server.h"

void launch(struct Server *server)
{
  char *hello = "HTTP/1.1 200 OK\n\n<!DOCTYPE html><html><head></head><body><h1>Hello</h1></body></html>";  
  int address_length = sizeof(server->address);
  char buffer[30000];
  int new_socket;
  while(1){
    
    printf("====== WAITING FOR CONNECTION ======\n");
    
    new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
    read(new_socket, buffer, 3000);
    printf("%s\n", buffer);

    
    write(new_socket, hello, strlen(hello));
    close(new_socket);
  }
}


int main()
{
  struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
  server.launch(&server);
}

