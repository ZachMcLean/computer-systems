# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -pthread

# Source Files
SRCS = server.c client.c csapp.c

# Object Files
OBJS = server.o client.o csapp.o

# Executable Files
TARGETS = server client

# Default target
all: $(TARGETS)

# Server target
server: server.o csapp.o
	$(CC) $(CFLAGS) -o server server.o csapp.o

# Client target
client: client.o csapp.o
	$(CC) $(CFLAGS) -o client client.o csapp.o

# Object file compilation
server.o: server.c csapp.h
	$(CC) $(CFLAGS) -c server.c

client.o: client.c csapp.h
	$(CC) $(CFLAGS) -c client.c

csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c csapp.c

# Clean target to remove generated files
clean:
	rm -f $(OBJS) $(TARGETS)

# Phony targets
.PHONY: all clean
