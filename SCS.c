#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include <netinet/in.h>

int main(int argc , char *argv[])
{
	int sock_acc, sock_client,port_no,client_length,n;
	struct sockaddr_in serv_addr, cli_addr;
	port_no = 5001;
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
	/*CODE FOR DATA SERVER*/
	int port_no2 = 5002;
	char *ip = "127.0.0.1";
	struct sockaddr_in ds;
	bzero((char *)&ds,sizeof(ds));
	ds.sin_family = AF_INET;
	struct hostent *ds_server;
	ds_server = gethostbyname(ip);
	int sock_acc2 = socket(AF_INET,SOCK_STREAM,0);
	if(ds_server==NULL)
	{
		perror("Data Server not found");
	}
	bcopy((char *)ds_server->h_addr,(char *)&ds.sin_addr.s_addr,ds_server->h_length);
	ds.sin_port=htons(port_no2);
	if(connect(sock_acc2,(struct sockaddr *)&ds,sizeof(ds))<0)
	{
		perror("Error while connecting\n");
	}
	char buffer2[256];
	bzero((char *)buffer2,256);
	//buffer2 = buffer;
	int temp = write(sock_acc2,buffer,sizeof(buffer));
	if(temp<0)
	{
		perror("Error reading from socket");
	}
	 memset(buffer,'/0',256);
   n = read(sock_acc2, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
/*END CODE FOR DATA SERVER*/

/*CODE FOR COMPUTE SERVER*/
	int port_no3 = 5003;
	struct sockaddr_in cs;
	bzero((char *)&cs,sizeof(cs));
	cs.sin_family = AF_INET;
	struct hostent *cs_server;
	cs_server = gethostbyname(ip);
	int sock_acc3 = socket(AF_INET,SOCK_STREAM,0);
	if(cs_server==NULL)
	{
		perror("Data Server not found");
	}
	bcopy((char *)cs_server->h_addr,(char *)&cs.sin_addr.s_addr,cs_server->h_length);
	cs.sin_port=htons(port_no3);
	if(connect(sock_acc3,(struct sockaddr *)&cs,sizeof(cs))<0)
	{
		perror("Error while connecting Compute Server\n");
	}
	//buffer2 = buffer;
	temp = write(sock_acc3,buffer,sizeof(buffer));
	if(temp<0)
	{
		perror("Error reading from socket");
	}
	 bzero(buffer,256);
   n = read(sock_acc3, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
/*END CODE FOR COMPUTE SERVER*/
 temp = write(sock_client,buffer,sizeof(buffer)); //Sending the final computed data back to end client
	if(temp<0)
	{
		perror("Error writing to socket");
	}
return 0;


}