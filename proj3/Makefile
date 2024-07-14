CC = gcc
CFLAGS = -Wall -Wextra -g
CSAPP_SRC = csapp.c
CSAPP_OBJ = csapp.o
CLIENT_SRC = client.c
CLIENT_OBJ = client.o
SERVER_SRC = server.c
SERVER_OBJ = server.o
TARGETS = client server

all: $(TARGETS)

$(CSAPP_OBJ): $(CSAPP_SRC)
	$(CC) $(CFLAGS) -c $<

$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -c $<

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $<

client: $(CLIENT_OBJ) $(CSAPP_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

server: $(SERVER_OBJ) $(CSAPP_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS) *.o
