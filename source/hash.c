#include"hash.h"

/*function to insert packet in hash table*/
void insert_packet(void *opn1,struct iptuppel *ptr)
{

	struct iptuppel *opn=(struct iptuppel *)opn1;
	/*variable to count no of packets arrived*/
	static int count;
	int i,index,j,ret;
	int source_bin;
	source_bin=inet_addr(ptr->s_ip);

	int dest_bin;
	dest_bin=inet_addr(ptr->d_ip);

	int s_port=ptr->sou_port;
	int d_port=ptr->des_port;

	index=calc_index(source_bin,dest_bin,s_port,d_port)%MAX;
	printf("index=%d\n",index);
	strcpy(opn[index].proto,ptr->proto);

	/*checking if packet from same source ip,destiantion ip,source port no,destination port no is their or not*/
	if((strcmp(ptr->s_ip,opn[index].s_ip) && strcmp(ptr->d_ip,opn[index].d_ip))==0 && d_port==opn[index].des_port)
	{
		/*if the 5 ip tuples are same it will update the TCP packet*/
		if(ret=(strcmp(opn[index].proto,"TCP"))==0)
	        {
		        printf("Updating TCP packet\n");
			count++;
			update_packet((void *)opn,index);
		}
		/*else it will update UDP packet*/
        	else
                {
			printf("Updating UDP packet\n");
			count++;
			update_packet((void *)opn,index);
		}
	}

	/*if not same it will insert that packet in hash table*/
	else
	{
		for(i=0;i<MAX;i++)
		{
			/*if already one packet is present at the index to avoid collision it will go to next empty location*/
			if(opn[index].des_port!=0)
			{
				index++;
				printf("updated index=%d\n",index);
			}
			/*inserting all 5 iptupples in hash table*/
			strcpy(opn[index].s_ip,ptr->s_ip);
			strcpy(opn[index].d_ip,ptr->d_ip);
			opn[index].sou_port=s_port;
			opn[index].des_port=d_port;
			strcpy(opn[index].proto,ptr->proto);
			strcpy(opn[index].data1,ptr->data1);
			opn[index].clk=time(NULL);
			/*function call to print all the 5 iptuppels present in hash table*/
			print((void *)opn,index);
			count++;
			break;
		}
		/*if index value reaches the last location of array then make index 0 to again start from 1st location*/
		if(index==(MAX-1))
		{
			index=0;
		}
		printf("total no of packets received %d\n",count);
	}
}

/*function to calculate index no*/
int calc_index(int source, int dest,int sport,int dport)
{
	int summ=0;
	summ=source+dest+dport+sport;
	return summ;
}

/*function to update packet*/
void update_packet(void *opn1,int index)
{
	struct iptuppel *opn=(struct iptuppel *)opn1;
	opn[index].clk=time(NULL);
	printf("timestamp=%s",ctime(&opn[index].clk));
}

/*function to search a packet in hash table*/
void lookup_packet(void *opn1,struct iptuppel *ptr)
{
	struct iptuppel *opn=(struct iptuppel *)opn1;
	int index;
	int var;
	char Ip_source[256];

	int s_bin=inet_addr(ptr->s_ip);
	int d_bin=inet_addr(ptr->d_ip);
	int s_port=ptr->sou_port;
        int d_port=ptr->des_port;
	index=calc_index(s_bin,d_bin,s_port,d_port)%MAX;
	printf("index=%d\n",index);
	printf("enter the source ip address\n");
	scanf(" %s",Ip_source);
	/*if entered ip address is same as ip address present in hash table it will print its location*/
	if(strcmp(Ip_source,opn[index].s_ip)==0 )
	{
		printf("packet with source address %s found on index %d and data is %s\n",opn[index].s_ip,index,opn[index].data1);
	}
	/*else it will print packet not found*/
	else
	{
		printf("packet not found\n");
	}
}
/*function to delete a packet*/
int delete_packet(void *opn1,struct iptuppel *ptr)
{
	struct iptuppel *opn=(struct iptuppel *)opn1;
	int index,var;
	char Ip_source[SIZE];
	int s_bin=inet_addr(ptr->s_ip);
	int d_bin=inet_addr(ptr->d_ip);
	int s_port=ptr->sou_port;
        int d_port=ptr->des_port;

	index=calc_index(s_bin,d_bin,s_port,d_port)%MAX;
	printf("enter the source ip address which packet you have to delete\n");
	scanf(" %s",Ip_source);
	/*if entered ip address is same as ip address present in hash table then it will delete the packet*/
	if(strcmp(Ip_source,opn[index].s_ip)==0)
	{
		opn[index].des_port=0;
		opn[index].sou_port=0;
	        return 0;
	}
	/*ip address not found then it will print invalid ip*/
	else
		return -1;

}

/*function to print all 5 iptuppels*/
void print(void *opn1, int index)
{

	struct iptuppel *opn=(struct iptuppel *)opn1;
	printf("source ip=%s\n",opn[index].s_ip);
        printf("dest ip=%s\n",opn[index].d_ip);
        printf("source port=%d\n",opn[index].sou_port);
        printf("destination port=%d\n",opn[index].des_port);
        printf("timestamp=%s",ctime(&opn[index].clk));
        printf("data received=%s\n",opn[index].data1);
}

