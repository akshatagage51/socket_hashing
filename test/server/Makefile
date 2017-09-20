CC=gcc
FLAGS= -I ../../include -g
EXECPATH= ../../
OBJPATH= ../../source/
LIBPATH= ../../source/
LIBNAME= libhash.a
LFLAGS= -lhash -L$(LIBPATH)

default: server clean

server: server.o $(LIBPATH)$(LIBNAME)
	$(CC) -o$(EXECPATH)server server.o $(LFLAGS) -lpthread -g
server.o: server.c
	$(CC) $(FLAGS) -c server.c
clean:
	rm -rf server.o
