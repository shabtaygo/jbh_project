#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "query.h"
#define PORT 12345
#define MAX_LEN 1024
typedef struct thread_args
{
    Customer **head;
    char *file_name;
    int new_sock;
    void (*show)(char *, int);
} thread_args;

void show(char *str, int new_sock)
{
    if (send(new_sock, str, strlen(str), 0) < 0)
    {
        perror("fialed sending");
    }
}

void *conn_handler(void *argst)
{
    char buffer[MAX_LEN];
    int n;
    thread_args *args = argst;

    n = recv(args->new_sock, buffer, MAX_LEN, 0);
    if (n < 0)
    {
        perror("Server error receiving data");
        goto exit;
    }
    buffer[n] = '\0';
    printf("Server received: %s\n", buffer);
    if (!strncmp(buffer, "create", 6))
    {
        create_db(args->file_name, args->head,
                  args->show, args->new_sock);
    }
    else
    {
        handl_query(buffer,args->head,
                    args->file_name, args->show, args->new_sock);
    }

    // sleep(2);

    //     strcpy(buffer, "Thanks from TCP server!");
    //     n = send(new_sock, buffer, strlen(buffer), 0);
    //     if (n < 0)
    //     {
    //         perror("Server error sending data");
    //         goto exit;
    //     }
     exit:
    close(args->new_sock);
    return NULL;
}

int main(int argc, char **argv)
{
    Customer *head = NULL;
    char buf[100] = {0};
    char file_name[] = "customers.txt";

    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    // create_db(file_name, &head, show, 0);
    // if (argc < 2)
    // {
    //     printf("Usage: %s <port>\n", argv[0]);
    //     return 1;
    // }

    /* Create a socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    /* Bind the socket to a specific port */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Error binding socket");
        return 1;
    }

    if (listen(sockfd, 5) < 0)
    {
        perror("Error listenning");
        return 1;
    }

    /* Receive data from clients */
    while (1)
    {
        pthread_t tid;
        int new_sock = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&len);
        if (new_sock < 0)
        {
            perror("accept failed");
            return 1;
        }
        thread_args args = {
            .head = &head,
            .file_name = file_name,
            .new_sock = new_sock,
            .show = show};
        pthread_create(&tid, NULL, conn_handler, (void *)&args);
        pthread_join(tid, NULL);
    }

    return 0;
}