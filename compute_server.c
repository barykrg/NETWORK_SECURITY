#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include <netinet/in.h>

int main(int argc , char *argv[])
{
	int sock_acc, sock_client,port_no,client_length,n;
	struct sockaddr_in serv_addr, cli_addr;
	port_no = 5003;
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
	memset(buffer,'/0',256);
	n = read(sock_client,buffer,255);
	if(n<0)
	{
		perror("Error Reading from socket");
	}
	
	int i = 0;
	int total = 0;
	int temp = 0;
	while(buffer[i]!='$')
	{
		if(buffer[i]!=',')
		{
			temp*=10;
			temp+=buffer[i]-'0';
		}
		else
		{
			total+=temp;
			temp=0;
		}
		i++;
	}
	total+=temp;
	bzero(buffer,256);
	sprintf(buffer,"%d",total);
   n = write(sock_client,buffer,sizeof(buffer));
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
	return 0;



}