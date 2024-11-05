#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include "config.h"

int main(){
  int sock;
  struct sockaddr_in server_addr;
  char pin[256];
  soc=socket(AF_INET,SOCK_STREAM,0);
  if(sock<0){
    perror("socket failed");
    exit(EXIT_FAILURE);
    
  }
  
  server_addr.sin_family= AF_INET;
  server_addr.sin_port= htons(SERVER_PORT);
  
  if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
  }
  if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
  }
  recv(sock, pin, sizeof(pin), 0);
  
printf("Enter your PIN: ");
  fgets(pin, sizeof(pin), stdin);
  send(sock, pin, strlen(pin), 0);

  recv(sock, pin, sizeof(pin), 0);
    printf("%s", pin);  // Print the server's response
  

  close(sock);
  return 0;
  
 
  
  
}
