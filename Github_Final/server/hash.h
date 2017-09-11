#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/ioctl.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <time.h>
#define MAX 1000
#define SIZE 256
struct packet{
		char source_ip[SIZE], dest_ip[SIZE];
		int source_port,dest_port;
                char data[SIZE];
		time_t clk;
		char protocol[SIZE];
        };

struct iptuppel{
		char s_ip[SIZE],d_ip[SIZE];
		int sou_port,des_port;
		char data1[SIZE];
		time_t clk;
		char proto[SIZE];
	};



void insert_packet(struct iptuppel opn[],struct packet *ptr);
int addition_digits(int source, int dest,int sport,int dport);
void update_packet(struct iptuppel opn[],int index);
void lookup_packet(struct iptuppel opn[],struct packet *ptr);
void delete_packet(struct iptuppel opn[],struct packet *ptr);
