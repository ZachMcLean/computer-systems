// Zach McLean
// Computer Systems

#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_SIZE 1024
#define PORT "3240"

// Reader-writer lock
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void *handle_client(void *connfd);
void add_record(char *record);
void search_by_name(char *name, int connfd);
void search_by_zip(char *zip, int connfd);
void search_by_salary(char *criteria, int connfd);

int main(void) {
    int listenfd, *connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];
    pthread_t tid;

    listenfd = Open_listenfd(PORT);

    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = malloc(sizeof(int));
        *connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE,
                    client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);

        // Create a new thread to handle the client
        pthread_create(&tid, NULL, handle_client, connfd);
    }

    return 0;
}

void *handle_client(void *vargp) {
    int connfd = *((int *)vargp);
    free(vargp);
    pthread_detach(pthread_self());

    rio_t rio;
    char buf[BUFFER_SIZE];
    ssize_t n;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, BUFFER_SIZE)) != 0) {
        buf[n] = '\0';
        printf("Received: %s\n", buf);

        char *command = strtok(buf, ":");
        if (strcmp(command, "ADD") == 0) {
            char *record = strtok(NULL, ":");
            if (record) {
                pthread_rwlock_wrlock(&rwlock); // Write lock
                printf("Adding record: %s\n", record);
                add_record(record);
                pthread_rwlock_unlock(&rwlock); // Unlock
                Rio_writen(connfd, "Record added successfully\n", 26);
            } else {
                Rio_writen(connfd, "Failed to add record\n", 20);
            }
        } else if (strcmp(command, "SEARCH_NAME") == 0) {
            char *name = strtok(NULL, ":");
            pthread_rwlock_rdlock(&rwlock); // Read lock
            search_by_name(name, connfd);
            pthread_rwlock_unlock(&rwlock); // Unlock
        } else if (strcmp(command, "SEARCH_ZIP") == 0) {
            char *zip = strtok(NULL, ":");
            pthread_rwlock_rdlock(&rwlock); // Read lock
            search_by_zip(zip, connfd);
            pthread_rwlock_unlock(&rwlock); // Unlock
        } else if (strcmp(command, "SEARCH_SALARY") == 0) {
            char *criteria = strtok(NULL, ":");
            pthread_rwlock_rdlock(&rwlock); // Read lock
            search_by_salary(criteria, connfd);
            pthread_rwlock_unlock(&rwlock); // Unlock
        } else if (strcmp(command, "TERMINATE") == 0) {
            Rio_writen(connfd, "Connection Closed\n", 18);
            break;
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    Close(connfd);
    printf("Client disconnected\n");
    return NULL;
}

void add_record(char *record) {
    FILE *file = fopen("records.csv", "a");
    if (file == NULL) {
        perror("File opening failed");
        return;
    }
    fprintf(file, "%s\n", record);
    fclose(file);
}

void search_by_name(char *name, int connfd) {
    FILE *file = fopen("records.csv", "r");
    if (file == NULL) {
        perror("File opening failed");
        return;
    }

    char line[BUFFER_SIZE];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, name) != NULL) {
            Rio_writen(connfd, line, strlen(line));
            found = 1;
        }
    }
    if (!found) {
        Rio_writen(connfd, "No record found\n", 16);
    }

    fclose(file);
}

void search_by_zip(char *zip, int connfd) {
    FILE *file = fopen("records.csv", "r");
    if (file == NULL) {
        perror("File opening failed");
        return;
    }

    char line[BUFFER_SIZE];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        for (int i = 0; i < 3; i++) {
            token = strtok(NULL, ",");
        }
        if (strcmp(token, zip) == 0) {
            Rio_writen(connfd, line, strlen(line));
            found = 1;
        }
    }
    if (!found) {
        Rio_writen(connfd, "No record found\n", 16);
    }

    fclose(file);
}

void search_by_salary(char *criteria, int connfd) {
    FILE *file = fopen("records.csv", "r");
    if (file == NULL) {
        perror("File opening failed");
        return;
    }

    char *salary_str = strtok(criteria, " ");
    char *operator = strtok(NULL, " ");
    int salary = atoi(salary_str);

    char line[BUFFER_SIZE];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        for (int i = 0; i < 4; i++) {
            token = strtok(NULL, ",");
        }
        int record_salary = atoi(token);

        int match = 0;
        if (strcmp(operator, ">") == 0 && record_salary > salary) match = 1;
        else if (strcmp(operator, "<") == 0 && record_salary < salary) match = 1;
        else if (strcmp(operator, ">=") == 0 && record_salary >= salary) match = 1;
        else if (strcmp(operator, "<=") == 0 && record_salary <= salary) match = 1;
        else if (strcmp(operator, "==") == 0 && record_salary == salary) match = 1;

        if (match) {
            Rio_writen(connfd, line, strlen(line));
            found = 1;
        }
    }
    if (!found) {
        Rio_writen(connfd, "No record found\n", 16);
    }

    fclose(file);
}
