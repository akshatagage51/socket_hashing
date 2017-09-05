#include"hash.h"

void insert_packet(struct packet *ptr,struct packet opn[], int source_bin,int dest_bin,int s_port,int d_port,char ch[]) 
{
	static int count;//variable to count no of packets sent
	char ip_str[256];
	int i,index,j;
	index=addition_digits(source_bin,dest_bin,s_port,d_port)%MAX;//MAX=SIZE of array, here we will get our index no
	printf("index:%d\n",index);

	if(source_bin==ptr->source_ip && dest_bin==ptr->dest_ip && s_port==ptr->source_port && d_port==ptr->dest_port)//checking if packet from same source ip,destiantion ip,source port no,destination port no is their or not
	{
		count++;
		update_packet(opn,index);//if the 5 ip tuples are same it will update the packet
	}
	else	//if not same it will insert that packet in hash table
	{
		for(i=0;i<MAX;i++)
		{
			if(opn[index].source_ip!=0)
			{
				index++;
				printf("updated index=%d\n",index);
			}
			opn[index].source_ip=source_bin;
			opn[index].dest_ip=dest_bin;
			opn[index].source_port=s_port;
			opn[index].dest_port=d_port;
			strcpy(opn[index].data,ch);
			opn[index].clk=time(NULL);
			printf("timestamp=%s",ctime(&opn[index].clk));
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
int addition_digits(int source,int dest,int sport,int dport)//function to calculate index no
{
	int summ=0;
	summ=addition(source)+summ;
	summ=addition(dest)+summ;
	summ=addition(sport)+summ;
	summ=addition(dport)+summ;
	return summ;
}

int addition(long num)
{
	long digit,sum=0;
	while(num>0)
	{
		digit=num%10;
		sum=sum+digit;
		num=num/10;
	}
	return sum;
}


void update_packet(struct packet opn[],int index)//function to update packet
{
	opn[index].clk=time(NULL);
	printf(" timestamp=%s",ctime(&opn[index].clk));//updating timestamp
	//count++;
}

void lookup(struct packet opn[],int source_bin,int dest_bin,int s_port,int d_port,char ipt_str[])//function to search a packet in hash table
{
	int index;
	int var;
	char Ip_source[256];
	printf("enter 1 to lookup else 2 \n");
	scanf("%d",&var);
	if(var==1)
	{
		printf("enter the source ip address\n");
		scanf("%s",Ip_source);
		gets();
		if(strcmp(Ip_source,ipt_str)==0)
		{
			index=addition_digits(source_bin,dest_bin,s_port,d_port)%MAX;//MAX=SIZE of array
			printf("packet with source address %s found on index %d and data is %s\n",ipt_str,index,opn[index].data);
		}
	}
	else
		return;

}
