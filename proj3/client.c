#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MESSAGE_SIZE 2048  // Increased size to avoid truncation

void add_record(int clientfd, rio_t *rio);
void search_by_name(int clientfd, rio_t *rio);
void search_by_zip(int clientfd, rio_t *rio);
void search_by_salary(int clientfd, rio_t *rio);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int clientfd;
    char *host = argv[1];
    char *port = argv[2];
    rio_t rio;

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    int option;
    while (1) {
        printf("(1) Add record\n(2) Search by Name\n(3) Search by Zip Code\n(4) Search by Salary\n(5) Terminate\n");
        printf("Select an option [1,2,3,4 or 5]: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                add_record(clientfd, &rio);
                break;
            case 2:
                search_by_name(clientfd, &rio);
                break;
            case 3:
                search_by_zip(clientfd, &rio);
                break;
            case 4:
                search_by_salary(clientfd, &rio);
                break;
            case 5:
                Rio_writen(clientfd, "TERMINATE", 9);
                Close(clientfd);
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Invalid option\n");
        }
    }

    Close(clientfd);
    return 0;
}

void add_record(int clientfd, rio_t *rio) {
    char buffer[BUFFER_SIZE];
    char record[BUFFER_SIZE];
    char message[MESSAGE_SIZE];

    printf("Enter First Name: ");
    scanf("%s", buffer);
    strcpy(record, buffer);
    strcat(record, ",");

    printf("Enter Last Name: ");
    scanf("%s", buffer);
    strcat(record, buffer);
    strcat(record, ",");

    printf("Enter Zip Code: ");
    scanf("%s", buffer);
    strcat(record, buffer);
    strcat(record, ",");

    printf("Enter Department: ");
    scanf("%s", buffer);
    strcat(record, buffer);
    strcat(record, ",");

    printf("Enter Salary: ");
    scanf("%s", buffer);
    strcat(record, buffer);

    snprintf(message, sizeof(message), "ADD:%s", record);
    Rio_writen(clientfd, message, strlen(message));

    if (Rio_readnb(rio, buffer, BUFFER_SIZE) > 0) {
        printf("Message From Server: %s\n", buffer);
    } else {
        printf("Failed to receive confirmation from server\n");
    }
}

void search_by_name(int clientfd, rio_t *rio) {
    char buffer[BUFFER_SIZE];
    char name[BUFFER_SIZE];
    char message[MESSAGE_SIZE];

    printf("Enter First Name: ");
    scanf("%s", buffer);
    strcpy(name, buffer);
    strcat(name, " ");

    printf("Enter Last Name: ");
    scanf("%s", buffer);
    strcat(name, buffer);

    snprintf(message, sizeof(message), "SEARCH_NAME:%s", name);
    Rio_writen(clientfd, message, strlen(message));

    if (Rio_readnb(rio, buffer, BUFFER_SIZE) > 0) {
        printf("Message From Server: %s\n", buffer);
    } else {
        printf("Failed to receive search result from server\n");
    }
}

void search_by_zip(int clientfd, rio_t *rio) {
    char buffer[BUFFER_SIZE];
    char zip[BUFFER_SIZE];
    char message[MESSAGE_SIZE];

    printf("Enter Zip Code: ");
    scanf("%s", buffer);
    strcpy(zip, buffer);

    snprintf(message, sizeof(message), "SEARCH_ZIP:%s", zip);
    Rio_writen(clientfd, message, strlen(message));

    if (Rio_readnb(rio, buffer, BUFFER_SIZE) > 0) {
        printf("Message From Server: %s\n", buffer);
    } else {
        printf("Failed to receive search result from server\n");
    }
}

void search_by_salary(int clientfd, rio_t *rio) {
    char buffer[BUFFER_SIZE];
    char criteria[BUFFER_SIZE];
    char message[MESSAGE_SIZE];

    printf("Enter Salary: ");
    scanf("%s", buffer);
    strcpy(criteria, buffer);
    strcat(criteria, " ");

    printf("Enter Comparison Type ['>', '<', '==', '>=', '<=']: ");
    scanf("%s", buffer);
    strcat(criteria, buffer);

    snprintf(message, sizeof(message), "SEARCH_SALARY:%s", criteria);
    Rio_writen(clientfd, message, strlen(message));

    if (Rio_readnb(rio, buffer, BUFFER_SIZE) > 0) {
        printf("Message From Server: %s\n", buffer);
    } else {
        printf("Failed to receive search result from server\n");
    }
}
