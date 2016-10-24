#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<time.h>
#include<stdlib.h>
int main(int argc , char *argv[])
{

int socket_desc , new_socket , c,i,j,Ans,CAns,AAns[4],ACAns[4],A=0,B=0,AC,AA;
struct sockaddr_in server , client;
char *message,str[4],re[100],rere[100];
time_t mytime;
mytime=time(NULL);
//Create socket
socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
printf("Could not create socket");
}
//Prepare the sockaddr_in structure
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons( 8787 );
//Bind
if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
{
puts("bind failed");
return 1;
}
puts("bind done");
//Listen
listen(socket_desc , 3);
//Accept and incoming connection
puts("Waiting for incoming connections...");
c = sizeof(struct sockaddr_in);
while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
{
puts("Connection accepted");
srand(time(NULL));
Ans = (rand()%8999)+1000;
printf("Ans:%d",Ans);
//Reply to the client
while(1)
{
A=0;
B=0;
AA = Ans;
bzero(str,4);
read(new_socket,str,4);
CAns = (str[0]-'0')*1000+(str[1]-'0')*100+(str[2]-'0')*10+(str[3]-'0');
ACAns[0] = CAns/1000;
CAns-=ACAns[0]*1000;
ACAns[1] = CAns/100;
CAns-=ACAns[1]*100;
ACAns[2] = CAns/10;
CAns-=ACAns[2]*10;
ACAns[3] = CAns/1;
AAns[0] = AA/1000;
AA-=AAns[0]*1000;
AAns[1] = AA/100;
AA-=AAns[1]*100;
AAns[2] = AA/10;
AA-=AAns[2]*10;
AAns[3] = AA/1;
for(i = 0;i<=3;i++)
{
if(ACAns[i]==AAns[i])
{
A++;
}
}
for(j=0;j<=3;j++)
{
for(i=0;i<=3;i++)
{
if(ACAns[i]==AAns[j]&&i!=j)
{
B++;
}
}
}
if(A==4)
{
message = "You Are RIGHT!!!";
write(new_socket , message, strlen(message)+1);
return 1;
}
else
{
sprintf(re,"%dA%dB",A,B);
write(new_socket , re, strlen(re)+1);
}


}
//message=ctime(&mytime);
//write(new_socket , message , strlen(message));
}
if (new_socket<0)
{
perror("accept failed");
return 1;
}
return 0;
}
