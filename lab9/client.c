#include "csapp.h"

int main(int argc, char *argv[])
{
    int clientfd; //file descriptor to communicate with the server
    char *host, *port;
    // size_t n;
    char buffer[MAXLINE]; //MAXLINE = 8192 defined in csapp.h

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }

    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port); //wrapper function that calls getadderinfo, socket, and connect functions

    // Getting a message from the user
    printf("Please enter the message: ");
    bzero(buffer, MAXLINE);
    Fgets(buffer, MAXLINE, stdin);

    // Sending the message received from the user to the server
    write(clientfd, buffer, strlen(buffer));
    bzero(buffer, MAXLINE);

    // Waiting for the message from the server
    read(clientfd, buffer, MAXLINE);
    printf("Message from Server: ");
    Fputs(buffer, stdout);

    /* TODO: 
    1. Add a code to send a new message to the server (you can ask the user to provide a new message in the terminal)
    2. Wait for the confirmation message (using read function) from the server and display it.
    */

    // Getting a new message from the user
    printf("Please enter the second message: ");
    bzero(buffer, MAXLINE);
    Fgets(buffer, MAXLINE, stdin);

    // Sending the second message to the server
    write(clientfd, buffer, strlen(buffer));
    bzero(buffer, MAXLINE);

    // Waiting for the confirmation message for the second message
    read(clientfd, buffer, MAXLINE);
    printf("Second Message from Server: ");
    Fputs(buffer, stdout);

    Close(clientfd);
    return 0;
}
