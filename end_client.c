#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<netinet/in.h>

int main(int argc,char *argv[])
{
	int port_no,sock_no,n;
	char buffer[256];
	if(argc<3)
	{
		perror("Enter proper host IP and port number\n");
		exit(1);
	}
	struct hostent *server;
	struct sockaddr_in serv_addr;
	port_no=atoi(argv[2]);
	server = gethostbyname(argv[1]);
	sock_no = socket(AF_INET,SOCK_STREAM,0);
	if(server==NULL)
	{
		perror("No such host is present\n");
		exit(0);
	}
	bzero((char*)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port=htons(port_no);
	if(connect(sock_no,(struct serv_addr *)&serv_addr,sizeof(serv_addr))<0)
	{
		perror("Error in Connection\n");
		exit(1);
	}
	bzero(buffer,256);
	printf("Enter the file number to work on and the operation to be done\n");
	scanf("%s",buffer);
	n=write(sock_no,buffer,sizeof(buffer));
	n=read(sock_no,buffer,sizeof(buffer));
	if(n<0)
	{
		perror("Error in reading\n");
		exit(1);
	}
	printf("%s\n",buffer );
	return 0;

}