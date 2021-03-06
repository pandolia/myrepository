#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAXPENDING 5        /* Max connection requests */
#define BUFSIZE 32

void Die(char *message) { perror(message); exit(1); }

void handleClient(int sock)
{
    char buf[BUFSIZE];
    int received = -1;
    while ((received = recv(sock, buf, sizeof(buf), 0))) {
        if (received < 0) {
            Die("Failed to receive bytes from client");
        }
        if (send(sock, buf, received, 0) != received) {
            Die("Failed to send bytes to client");
        }
    }
    close(sock);
}

int main(int argc, char *argv[])
{
    int serversock, clientsock;
    struct sockaddr_in echoserver, echoclient;

    if (argc != 3) {
        fprintf(stderr, "USAGE: %s <address> <port>\n", argv[0]);
        return 1;
    }

    /* Create the TCP socket */
    if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        Die("Failed to create socket");
    }

    /* Construct the server sockaddr_in structure */
    memset(&echoserver, 0, sizeof(echoserver));          /* Clear the structure */
    echoserver.sin_family = AF_INET;                    /* Internet/IP */
    echoserver.sin_addr.s_addr = inet_addr(argv[1]);    /* Incoming addr */
    echoserver.sin_port = htons(atoi(argv[2]));         /* Server port */

    /* Bind the server socket */
    if (bind(serversock,
             (struct sockaddr *) &echoserver,
             sizeof(echoserver)) < 0) {
        Die("Failed to bind the server socket");
    }

    /* Listen on the server socket */
    if (listen(serversock, MAXPENDING) < 0) {
        Die("Failed to listen on server socket");
    }

    /* Run until cancelled */
    while (1) {
        unsigned int clientlen = sizeof(echoclient);
        /* Waiting for client connection */
        if ((clientsock = accept(serversock,
                                 (struct sockaddr *) &echoclient,
                                 &clientlen)) < 0) {
            Die("Failed to accept client connection");
        }
        fprintf(stdout, "Client connected: %s\n",
                inet_ntoa(echoclient.sin_addr));
        handleClient(clientsock);
    }
}
