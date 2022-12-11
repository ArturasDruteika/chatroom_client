#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "../../headers/client/client.h"
#include "../../headers/utils/utils.h"


#define PORT 8080
#define HOSTNAME "127.0.0.1"


void client_connect()
{
    int sockfd, response;

    struct sockaddr_in serv_addr{};
    struct hostent *serverAddr;

    serverAddr = gethostbyname(HOSTNAME);

    char buffer[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    if (serverAddr == nullptr)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) serverAddr->h_addr, (char *) &serv_addr.sin_addr.s_addr, serverAddr->h_length);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    response = read(sockfd, buffer, 255);

    if (response < 0)
        error("ERROR reading from socket");

    printf("%s\n", buffer);

    int i = 0;

    while (true)
    {
        printf("Please enter the message: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        response = write(sockfd, buffer, strlen(buffer));

        if (response < 0)
            error("ERROR writing to socket");

        bzero(buffer, 256);
        response = read(sockfd, buffer, 255);

        if (response < 0)
            error("ERROR reading from socket");

        printf("%s\n", buffer);

        if (i == 10) break;
        i += 1;
    }

    close(sockfd);
}