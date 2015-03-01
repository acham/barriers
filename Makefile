CC=mpicc
CFLAGS=-I.  -Wall -g
# COMMON_DEPS =  utils.o ipclib.h utils.h
# CLIENT_DEPS = ipclib.o  
OBJ = server.o client.o 
LIBS= -lm -lpthread

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

server: server.o $(COMMON_DEPS)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

client: client.o $(CLIENT_DEPS) $(COMMON_DEPS)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

async_client: async_client.o $(CLIENT_DEPS) $(COMMON_DEPS)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

test_sync_async_client: test_sync_async_client.o $(CLIENT_DEPS) $(COMMON_DEPS)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)


all: server client async_client test_sync_async_client

.PHONY: clean

clean :
	rm *.o server client async_client  test_sync_async_client client00* server.log
