CC=gcc

default: server clean

server: server.o hash.o
	$(CC) -o server server.o hash.o -g

server.o: server.c
	$(CC) $(FLAGS) -c server.c
hash.o: $(OBJPATH)hash.c
	$(CC) $(FLAGS) -c $(OBJPATH)hash.c

libhash: ar -crv libhash.a server.o hash.o

clean:
	rm -rf server.o hash.o
