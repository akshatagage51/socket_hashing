#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<sys/time.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include <time.h>
#define MAX 50
struct packet{
		int source_ip,dest_ip,source_port,dest_port;
                char data[256];
                time_t clk;
        };

/*struct node{
                char data[256];
                struct node *next;
        };
void separate_chaining(struct node *[],char [],int);
struct node *add_end(struct node *,char []);
void disp1(struct node *[]);
void disp2(struct node *);*/

void insert_packet(struct packet *,struct packet opn[], int ,int ,int ,int ,char []);
int addition_digits(int , int ,int , int);
int addition(long );
void update_packet(struct packet opn[],int );
void lookup(struct packet opn[],int ,int ,int ,int,char [] );




//void disp(struct packet []);
//void lookup(struct packet [],int);

