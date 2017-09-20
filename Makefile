SERVER_PATH= test/server
CLIENT_PATH= test/clients
LIB_PATH= source/
LIBNAME= libhash.a

all:
	$(MAKE) -C $(LIB_PATH)
	$(MAKE) -C $(SERVER_PATH)
	$(MAKE) -C $(CLIENT_PATH)

clean:
	rm -rf server client_tcp client_udp $(LIB_PATH)$(LIBNAME) 

