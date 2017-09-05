
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define SIZE 50
int main()
{
	 int sockfd,len,result;
	struct sockaddr_in address;
	char ch[SIZE],buffer[SIZE];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("192.168.131.32");
	address.sin_port=htons(8888);
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if(result==-1)
		perror("error:client1");


		printf("enter msg\n");
		scanf("%[^\n]s",ch);
		write(sockfd,ch,sizeof(ch));

	close(sockfd);
}
