CFLAGS = -Wall -std=c89

# make rule primaria con dummy target ‘all’
all: server client

server: server.o dir_server/utility_server.o lib/funzioni.o
	gcc $(CFLAGS) server.o dir_server/utility_server.o lib/funzioni.o -o server

client: client.o dir_client/utility_client.o lib/funzioni.o
	gcc $(CFLAGS) client.o dir_client/utility_client.o lib/funzioni.o -o client
	gcc $(CFLAGS) client.o dir_client/utility_client.o lib/funzioni.o -o other

server.o: server.c
	gcc $(CFLAGS) -c server.c -o server.o

client.o: client.c
	gcc $(CFLAGS) -c client.c -o client.o

dir_server/utility_server.o: dir_server/utility_server.h dir_server/utility_server.c
	gcc $(CFLAGS) -c dir_server/utility_server.c -o dir_server/utility_server.o

dir_client/utility_client.o: dir_client/utility_client.h dir_client/utility_client.c
	gcc $(CFLAGS) -c dir_client/utility_client.c -o dir_client/utility_client.o

lib/funzioni.o: lib/funzioni.h lib/funzioni.c
	gcc $(CFLAGS) -c lib/funzioni.c -o lib/funzioni.o

# pulizia dei file obj (da terminale)
clean:
	rm *o dir_server/*.o dir_client/*.o lib/*.o client server other