#include"hash.h"

void insert_packet(struct iptuppel opn[],struct packet *ptr)
{


	/*variable to count no of packets sent*/
	static int count;
	int i,index,j,ret;
	int source_bin;
	source_bin=inet_addr(ptr->source_ip);

	int dest_bin;
	dest_bin=inet_addr(ptr->dest_ip);

	int s_port=ptr->source_port;
	int d_port=ptr->dest_port;

	/*MAX=SIZE of array, here we will get our index no*/
	index=addition_digits(source_bin,dest_bin,s_port,d_port)%MAX;
	printf("index:%d\n",index);
	strcpy(opn[index].proto,ptr->protocol);

	/*checking if packet from same source ip,destiantion ip,source port no,destination port no is their or not*/
	if((strcmp(ptr->source_ip,opn[index].s_ip) && strcmp(ptr->dest_ip,opn[index].d_ip))==0 && d_port==opn[index].des_port)
	{
		 /*if the 5 ip tuples are same it will update the packet*/
		if(ret=(strcmp(opn[index].proto,"TCP"))==0)
	        {
		        printf("Updating TCP packet\n");
			count++;
			update_packet(opn,index);
		}
        	else
                {
			printf("Updating UDP packet\n");
			count++;
			update_packet(opn,index);
		}
	}

	/*if not same it will insert that packet in hash table*/
	else 
	{
		for(i=0;i<MAX;i++)
		{
			if(opn[index].des_port!=0)
			{
				index++;
				printf("updated index=%d\n",index);
			}
			strcpy(opn[index].s_ip,ptr->source_ip);
			strcpy(opn[index].d_ip,ptr->dest_ip);
			opn[index].sou_port=s_port;
			opn[index].des_port=d_port;
			strcpy(opn[index].proto,ptr->protocol);
			strcpy(opn[index].data1,ptr->data);
			opn[index].clk=time(NULL);

			printf("source ip=%s\n",opn[index].s_ip);
			printf("dest ip=%s\n",opn[index].d_ip);
			printf("source port=%d\n",opn[index].sou_port);
			printf("destination port=%d\n",opn[index].des_port);
			printf("timestamp=%s",ctime(&opn[index].clk));
			printf("data received=%s\n",opn[index].data1);
			count++;
			break;
		}
		if(index==(MAX-1))
		{
			index=0;
		}
		printf("total no of packets received %d\n",count);
	}
}

/*function to calculate index no*/
int addition_digits(int source, int dest,int sport,int dport)
{
	int summ=0;
	summ=source+dest+dport;
	return summ;
}

/*function to update packet*/
void update_packet(struct iptuppel opn[],int index)
{
	opn[index].clk=time(NULL);
	/*updating timestamp*/
	printf(" updated timestamp=%s",ctime(&opn[index].clk));
}
/*function to search a packet in hash table*/
void lookup_packet(struct iptuppel opn[],struct packet *ptr)
{
	int index;
	int var;
	char Ip_source[256];

	int s_bin=inet_addr(ptr->source_ip);
	int d_bin=inet_addr(ptr->dest_ip);
	int s_port=ptr->source_port;
        int d_port=ptr->dest_port;
	index=addition_digits(s_bin,d_bin,s_port,d_port)%MAX;

	printf("enter the source ip address\n");
	scanf(" %s",Ip_source);

	if(strcmp(Ip_source,opn[index].s_ip)==0 && opn[index].des_port==0 && opn[index].sou_port==0)
	{
		printf("packet with source address %s found on index %d and data is %s\n",opn[index].s_ip,index,opn[index].data1);
	}
	else
	{
		printf("packet not found\n");
	}
}
/*function to delete a packet*/
void delete_packet(struct iptuppel opn[],struct packet *ptr)
{
	int index,var;
	char Ip_source[SIZE];
	int s_bin=inet_addr(ptr->source_ip);
	int d_bin=inet_addr(ptr->dest_ip);
	int s_port=ptr->source_port;
        int d_port=ptr->dest_port;

	index=addition_digits(s_bin,d_bin,s_port,d_port)%MAX;
	printf("enter the source ip address which packet you have to delete\n");
	scanf(" %s",Ip_source);

	if(strcmp(Ip_source,ptr->source_ip)==0)
	{
		opn[index].des_port=0;
		opn[index].sou_port=0;
	        printf("packet deleted sucessfully\n");
	        printf("opn[index].des_port=%d\n",opn[index].des_port);
	        printf("opn[index].source_ip=%s\n",opn[index].s_ip);
	}
	else
		printf("Invalid source IP");

}
