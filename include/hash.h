#ifndef __HASH_H
#define __HASH_H

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
/*
 *MAX=SIZE of array, here we will get our index no
 */
#define MAX 1000
#define SIZE 256

/*
 *structure ip tupple consist of source ip address, destination ip address,source port no,
 * destination port no, a field to update timestamp, protocol and data received
 */

struct iptuppel{
		char s_ip[SIZE],d_ip[SIZE];
		int sou_port,des_port;
		char data1[SIZE];
		time_t clk;
		char proto[SIZE];
	};



/*
 *insert_packet function is used to insert the packet which we receive from client.
 *The packet consist of source ip, destination ip,source port,destination port,protocol,data and timestamp
 */
void insert_packet(void *opn1,struct iptuppel *ptr);

/*
 *In update_packet function if a packet comes from same 5 iptupples then the packet gets updated.
 *If not then it will simply insert the packet into hash table
 */
void update_packet(void *opn1,int index);

/*
 *In lookup_packet function if we have to lookup for a particular packet then it  will search in the hash table for that packet
 *and if found it will print its index no and ip address and if not it will print packet not found
 */
void lookup_packet(void *opn1,struct iptuppel *ptr);

/*
 *In delete_packet function if we want to delete a packet of a particular ip address then it will search that packet 
 *and will delete it
 */
int delete_packet(void *opn1,struct iptuppel *ptr);

/*
 *print function is used to print all the iptuppels in hash table
 */
void print(void *opn1, int index);

/*
 *calc_index function is used to calculate the index value based on source ip, destination ip, source port, destination port
 */
int calc_index(int source, int dest,int sport,int dport);

#endif
