#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT1 8080
#define PORT2 8090
int countServer1=0;
int countServer2=0;

int main(int argc, char const* argv[])
{
printf("usage: ./client {ip address}\n");
int sock = 0, valread, client_fd,sock2,client_fd2;
char command[1024];
struct sockaddr_in serv_addr;

if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
{
printf("\n Socket creation error \n");
return -1;
}
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT1);

//Convert IPv4 and IPv6 addresses from text to binary
// form

//if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) 
if (inet_pton(AF_INET, argv[1] , &serv_addr.sin_addr) <= 0) 
{
printf("\nInvalid address/ Address not supported \n");
return -1;
}
if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))< 0) 
{
printf("\nConnection Failed \n");
return -1;
}
char sc1[2];
valread=read(sock, sc1, 2);
sscanf(sc1, "%d", &countServer1);
if(countServer1<=5 || (countServer1>10 && countServer1%2==1))
{
printf("\ncountServer1:%d\n",countServer1);
function(sock);
close(client_fd);
return 0;
}

else{
if ((sock2 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
printf("\n Socket creation error \n");
return -1;
}
serv_addr.sin_port = htons(PORT2);
int client_fd2;
if ((client_fd2 = connect(sock2, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))< 0) 
{
printf("\nConnection Failed \n");
return -1;
}
char sc2[2];
valread=read(sock2, sc2, 2);
sscanf(sc2, "%d", &countServer2);
if(countServer2>10)countServer2=countServer1;
printf("\ncountServer2:%d\n",countServer2);
function(sock2);
close(client_fd2);
return 0;
}
}    


void function(int sock)
{
char command[50];
while(1){
bzero(command,1024);
printf("\nenter the command:\n");
fgets(command,1024,stdin);

if((send(sock, command, strlen(command), 0))== -1)
{
fprintf(stderr, "Failure Sending Message\n");
close(sock);
exit(1);
}
else
{
char buffer[1024] = { 0 };
if(!strcmp(command,"quit\n"))
exit(0);
printf("\ncommand sent\n");
sleep(1);
int valread = read(sock, buffer, 1024);
printf("%s\n", buffer);
bzero(buffer,1024);
}
}
}



