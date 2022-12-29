#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#define PORT1 8080
#define PORT2 8090
int countServer1=5;
int main(int argc, char const* argv[])
{
int server_fd, new_socket,pid,csd;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);

// Creating socket file descriptor
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
perror("socket failed");
exit(EXIT_FAILURE);
}

// Forcefully attaching socket to the port 8080
if (setsockopt(server_fd, SOL_SOCKET,
SO_REUSEADDR | SO_REUSEPORT, &opt,
sizeof(opt))) {
perror("setsockopt");
exit(EXIT_FAILURE);
}
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT2);

// Forcefully attaching socket to the port 8080
if (bind(server_fd, (struct sockaddr*)&address,
sizeof(address))
< 0) {
perror("bind failed");
exit(EXIT_FAILURE);
}
if (listen(server_fd, 100) < 0) {
perror("listen");
exit(EXIT_FAILURE);
}

while(1)
{
csd=accept(server_fd,(struct sockaddr*)NULL,NULL);
countServer1=countServer1+1;
char cs[2];
sprintf(cs,"%d",countServer1);
int valread = write(csd, cs, 2);
if(fork()==0)
serviceClient(csd);
close(csd);
}
return 0;
}

void serviceClient(int new_socket)
{
char buffer[1024] = { 0 };
int valread;
while(1)
{
bzero(buffer , 1024);
valread = read(new_socket, buffer, 1024);
buffer[valread]='\0';
printf("%s\n", buffer);
if(valread < 0)
{
perror("error on reading");
}
if(!strcasecmp(buffer, "quit\n"))
exit(0);
else{
dup2(new_socket,1);
printf("\nserver2\n");
int n=system(buffer);
printf("\nresult sent\n");
}
} 
}
