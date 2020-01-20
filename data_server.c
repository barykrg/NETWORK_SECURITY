#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include <netinet/in.h>

int main(int argc , char *argv[])
{
	int sock_acc, sock_client,port_no,client_length,n;
	struct sockaddr_in serv_addr, cli_addr;
	port_no = 5002;
	sock_acc = socket(AF_INET,SOCK_STREAM,0);
	if(sock_acc<0)
	{
		perror("Error in opening the socket\n");
		exit(1);
	}
	bzero((char *) &serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(port_no);
	if(bind(sock_acc,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		perror("Error on binding\n");
		exit(1);
	}
	listen(sock_acc,5);
	client_length=sizeof(cli_addr);
	sock_client=accept(sock_acc,(struct sockaddr *)&cli_addr,&client_length);
	if(sock_client<0)
	{
		perror("Error on accept\n");
		exit(1);
	}
	char buffer[256];
	bzero(buffer,256);
	n = read(sock_client,buffer,255);
	if(n<0)
	{
		perror("Error Reading from socket");
	}
	FILE *ptr = fopen(buffer,"r");
	if(ptr==NULL)
	{
		perror("File Not Present");
		exit(0);
	}
	char file[1000];
	fscanf(ptr,"%[^\n]",file);
	n = write(sock_client,file,sizeof(file));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
return 0;


}