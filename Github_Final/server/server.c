#include"hash.h"

int main()
{
        int server_sockfd,client_sockfd,vara,u_serverfd,u_clientfd,result,maxfd,ret,
		server_len,client_len,slen,res,s_port,d_port,len,source_bin,dest_bin;
	/*variable to sockaddr_in structure */
        struct sockaddr_in server_address,my_addr,client_address,  cli_addr;
        fd_set readfds,testfds;
	char ch[SIZE],ip_str[SIZE],ipt_str[SIZE],proto[SIZE],proto_udp[SIZE];
	struct iptuppel opnadd[MAX]={0};
	struct packet *ptr;
	/*allocating dynamic memory to pointer*/
	ptr=(struct packet *)malloc(sizeof(struct packet));
	/*creating TCP socket*/
	if((server_sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
		perror("TCP error\n");
	else
		printf("TCP sucessfull\n");
	/*filling the structure with family name, IP address, Port no*/
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("192.168.131.32");
	server_address.sin_port=htons(8888);
	server_len=sizeof(server_address);
	client_len=sizeof(client_address);

	/*binding ip address and port no to TCP socket*/
	if((bind(server_sockfd,(struct sockaddr *)&server_address,server_len))==-1)
		perror("Bind error\n");
	else
		printf("Bind sucessfull\n");
	/*listening for some activity to happen*/
	listen(server_sockfd,5);
	/*creating uDP socket*/
	if ((u_serverfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		perror("socket error\n");
	else
	      printf("udp successful\n");

	/*filling the structure with family name, IP address, Port no*/
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8888);
	my_addr.sin_addr.s_addr = inet_addr("192.168.131.32");
	slen=sizeof(my_addr);

	/*binding ip address and port no to UDP socket*/
	if (bind(u_serverfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)//binding udp socket
	      printf("bind error\n");
	else
	      printf("udp bind successful\n");
	while(1)
	{
		printf("\n");
		printf("server waiting\n");
		/*initializing readfds to zero*/
		FD_ZERO(&readfds);		
		FD_SET(u_serverfd,&readfds);
		FD_SET(server_sockfd,&readfds);
		if(u_serverfd>server_sockfd)
			maxfd=u_serverfd;
		else
			maxfd=server_sockfd;
		result=select(maxfd+1, &readfds, NULL, NULL, NULL);
		if(ret==-1)
		{
			perror("select");
			return -1;
		}
		/*if packet is tcp if condition will be true*/
		if(FD_ISSET(server_sockfd,&readfds))
		{
			printf("receiving Tcp packet\n");
			int flag=1;
			client_sockfd=accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
			strcpy(ptr->protocol,"TCP");
			/*used to know who is there at the other end of connected stream*/
			getsockname(server_sockfd,(struct sockaddr *)&server_address,&server_len);

			/*used to get ip address of local  machine*/
			getpeername(client_sockfd,(struct sockaddr *)&client_address,&client_len);

			strcpy(ptr->dest_ip,inet_ntoa(server_address.sin_addr));
			strcpy(ptr->source_ip,inet_ntoa(client_address.sin_addr));

			d_port=htons(server_address.sin_port);
			ptr->dest_port=d_port;

			/*gives port no of client machine*/
			s_port=htons(client_address.sin_port);
			ptr->source_port=s_port;

			read(client_sockfd,ch,sizeof(ch));
			strcpy(ptr->data,ch);

			/*inserting packet in hash table*/
			insert_packet((void *)opnadd,ptr);
			/*searching packet in hash table*/
			if(strcmp(ch,"lookup")==0)
				lookup_packet(opnadd,ptr);
			if(strcmp(ch,"delete")==0)
                                delete_packet(opnadd,ptr);
		}
		/*if packet is udp if condition will be true*/
		if(FD_ISSET(u_serverfd,&readfds))
		{

			len=sizeof(cli_addr);
			printf("receving udp packet\n");
			if (recvfrom(u_serverfd,ch, 256, 0, (struct sockaddr*)&cli_addr, &slen)==-1)
            			printf("recvfrom()");
			strcpy(ptr->protocol,"UDP");

			d_port=htons(my_addr.sin_port);
			ptr->dest_port=d_port;

			s_port=htons(cli_addr.sin_port);
			ptr->source_port=s_port;

			getsockname(u_serverfd,(struct sockaddr *)&my_addr,&slen);
			strcpy(ptr->dest_ip,inet_ntoa(my_addr.sin_addr));

			getpeername(u_serverfd,(struct sockaddr *)&cli_addr,&len);
			strcpy(ptr->source_ip,inet_ntoa(cli_addr.sin_addr));

			strcpy(ptr->data,ch);

			insert_packet(opnadd,ptr);
			if(strcmp(ch,"lookup")==0)
				lookup_packet(opnadd,ptr);
			if(strcmp(ch,"delete")==0)
				delete_packet(opnadd,ptr);

		}
	}
		close(u_serverfd);
		close(server_sockfd);
		free(ptr);
}


