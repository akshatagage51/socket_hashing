#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 256

/*void err(char *s)
{
    perror(s);
    exit(1);
}*/

int main(int argc, char** argv)
{
	struct sockaddr_in serv_addr;
	int sockfd, i, slen=sizeof(serv_addr),port_no;
	char buf[SIZE];

	if(argc != 3)
	{
		printf("Usage : %s <Server-IP>\n",argv[0]);
		exit(0);
	}

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		perror("socket");

	port_no=atoi(argv[2]);
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port =htons(port_no);
	if (inet_aton(argv[1], &serv_addr.sin_addr)==0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	while(1)
	{
		printf("\nEnter data to send(Type exit and press enter to exit) : ");
		scanf("%[^\n]",buf);
		getchar();
		if(strcmp(buf,"exit") == 0)
			exit(0);

		if (sendto(sockfd, buf, SIZE, 0, (struct sockaddr*)&serv_addr, slen)==-1)
			perror("sendto()");
	}
	close(sockfd);
	return 0;
}
