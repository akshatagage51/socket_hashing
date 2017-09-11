
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define SIZE 50
int main(int argc, char** argv)
{
	int sockfd, len, result,port_no;
	struct sockaddr_in address;
	char ch[SIZE], buffer[SIZE];

	if(argc != 3)
	{
		printf("usage : %s <server-ip\n>",argv[0]);
		exit(0);
	}

	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1)
		perror("socket");

	port_no=atoi(argv[2]);
	address.sin_family = AF_INET;
	address.sin_port = htons(port_no);
	if(inet_aton(argv[1], &address.sin_addr)==0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	len = sizeof(address);
	result = connect(sockfd,(struct sockaddr *)&address,len);
	if(result == -1)
		perror("error:client1");
	printf("enter msg\n");
	scanf("%[^\n]s",ch);
	write(sockfd,ch,sizeof(ch));
	close(sockfd);
}
