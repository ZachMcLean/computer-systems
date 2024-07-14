#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define MESSAGE_SIZE 2048  // Increased size to avoid truncation


void add_record(int socket);
void search_by_name(int socket);
void search_by_zip(int socket);
void search_by_salary(int socket);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    int option;
    while (1) {
        printf("(1) Add record\n(2) Search by Name\n(3) Search by Zip Code\n(4) Search by Salary\n(5) Terminate\n");
        printf("Select an option [1,2,3,4 or 5]: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                add_record(client_socket);
                break;
            case 2:
                search_by_name(client_socket);
                break;
            case 3:
                search_by_zip(client_socket);
                break;
            case 4:
                search_by_salary(client_socket);
                break;
            case 5:
                send(client_socket, "TERMINATE", 9, 0);
                close(client_socket);
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Invalid option\n");
        }
    }

    close(client_socket);
    return 0;
}

void add_record(int socket) {
    char buffer[BUFFER_SIZE];
    char first_name[50], last_name[50], zip_code[10], department[50];
    int salary;

    printf("Enter First Name: ");
    scanf("%s", first_name);
    printf("Enter Last Name: ");
    scanf("%s", last_name);
    printf("Enter Zip Code: ");
    scanf("%s", zip_code);
    printf("Enter Department: ");
    scanf("%s", department);
    printf("Enter Salary: ");
    scanf("%d", &salary);

    snprintf(buffer, sizeof(buffer), "ADD:%s,%s,%s,%s,%d", first_name, last_name, zip_code, department, salary);
    send(socket, buffer, strlen(buffer), 0);

    recv(socket, buffer, sizeof(buffer), 0);
    printf("Message From Server: %s\n", buffer);
}

void search_by_name(int socket) {
    char buffer[BUFFER_SIZE];
    char first_name[50], last_name[50];

    printf("Enter First Name: ");
    scanf("%s", first_name);
    printf("Enter Last Name: ");
    scanf("%s", last_name);

    snprintf(buffer, sizeof(buffer), "SEARCH_NAME:%s %s", first_name, last_name);
    send(socket, buffer, strlen(buffer), 0);

    while (recv(socket, buffer, sizeof(buffer), 0) > 0) {
        printf("Message From Server: %s\n", buffer);
    }
}

void search_by_zip(int socket) {
    char buffer[BUFFER_SIZE];
    char zip_code[10];

    printf("Enter Zip Code: ");
    scanf("%s", zip_code);

    snprintf(buffer, sizeof(buffer), "SEARCH_ZIP:%s", zip_code);
    send(socket, buffer, strlen(buffer), 0);

    while (recv(socket, buffer, sizeof(buffer), 0) > 0) {
        printf("Message From Server: %s\n", buffer);
    }
}

void search_by_salary(int socket) {
    char buffer[BUFFER_SIZE];
    int salary;
    char operator[3];

    printf("Enter Salary: ");
    scanf("%d", &salary);
    printf("Enter Comparison Operator [>,<,==,>=,<=]: ");
    scanf("%s", operator);

    snprintf(buffer, sizeof(buffer), "SEARCH_SALARY:%d %s", salary, operator);
    send(socket, buffer, strlen(buffer), 0);

    while (recv(socket, buffer, sizeof(buffer), 0) > 0) {
        printf("Message From Server: %s\n", buffer);
    }
}
