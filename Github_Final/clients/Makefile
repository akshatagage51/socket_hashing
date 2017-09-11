CC=gcc

default: client_tcp client_udp clean

client_tcp: client_tcp.o
	$(CC) -o client_tcp client_tcp.o -g

client_udp: client_udp.o
	$(CC) -o client_udp client_udp.o -g

client_tcp.o: client_tcp.c
	$(CC) -c $(FLAGS) client_tcp.c
client_udp.o: client_udp.c
	$(CC) -c $(FLAGS) client_udp.c
clean:
	rm -rf client_tcp.o client_udp.o


