#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LEN 1024
#define PORT 12345
void init(int sockfd, struct sockaddr_in *servaddr, unsigned len)
{
    int n, r;
    char buffer[MAX_LEN];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return;
    }
    if (connect(sockfd, (struct sockaddr *)servaddr, len) < 0)
    {
        perror("Error connecting");
        return;
    }
    strcpy(buffer, "create");
    printf("init mode=%d\n",sockfd);
    n = send(sockfd, buffer, strlen(buffer), 0);
    if (n < 0)
    {
        perror("Client error sending data");
        return;
    }
    r = 0;
    do
    {
        n = recv(sockfd, buffer + r, MAX_LEN - r, 0);
        if (n < 0)
        {
            perror("Client error receiving data");
            return;
        }
        r += n;
    } while (n);
    buffer[r] = '\0';
    printf("received: %s", buffer);
    close(sockfd);
}
int main(int argc, char **argv)
{
    int sockfd[5];
    struct sockaddr_in servaddr;
    char buffer[6][MAX_LEN];

    // if (argc < 2)
    // {
    //     printf("Usage: %s <port>\n", argv[0]);
    //     return 1;
    // }

    /* Connect to the server */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_port = htons(PORT);
    init(sockfd[0], &servaddr, sizeof(servaddr));
    /* Send data to the server */
    while (1)
    {
        int n = 0;
        int i = 0;
        int r = 0;
        int requests_amounts;
        for (size_t i = 0; i < 5; i++)
        {
            memset(buffer[i], 0, sizeof(buffer[i]));
        }
        memset(sockfd, 0, sizeof(sockfd));

        puts("Enter maximum 5 messages: and then <send> command");
        while (i < 6)
        {
            fgets(buffer[i], MAX_LEN, stdin);
            if (!strncmp(buffer[i], "send", 4))
            {
                break;
            }
            if (!strncmp(buffer[i], "quit", 4))
            {
                if (!i)
                {
                    return 0;
                }
                break;
            }
            i++;
        }
        if (i == 6)
        {
            puts("For sending requests please enter <send> command");
            continue;
        }
        if (i == 0)
        {
            puts("You must enter at least one request");
            continue;
        }

        requests_amounts = i;

        /* Create a sockets */
        i = 0;
        while (i < requests_amounts)
        {
            sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd[i] < 0)
            {
                perror("Error creating socket");
                return 1;
            }
            if (connect(sockfd[i], (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
            {
                perror("Error connecting");
                return 1;
            }
            i++;
        }
        i = 0;
        while (i < requests_amounts)
        {
            n = send(sockfd[i], buffer[i], strlen(buffer[i]) - 1, 0);
            printf("client mode=%d\n",sockfd[i]);
            if (n < 0)
            {
                perror("Client error sending data");
                return 1;
            }
            shutdown(sockfd[i], SHUT_WR);
            i++;
        }
        i = 0;
        while (i < requests_amounts)
        {
            r = 0;
            do
            {
                n = recv(sockfd[i], buffer[i] + r, MAX_LEN - r, 0);
                if (n < 0)
                {
                    perror("Client error receiving data");
                    return 1;
                }
                r += n;
            } while (n);

            // n = recv(sockfd[i], buffer[i], MAX_LEN, 0);
            // if (n < 0)
            // {
            //     perror("Client error receiving data");
            //     return 1;
            // }
            buffer[i][r] = '\0';
            printf("Client %d received: %s", i, buffer[i]);
            close(sockfd[i]);
            i++;
        }
    }

    return 0;
}
