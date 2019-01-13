/**
     * BroadcastReciever
     * This Client / Server package is designed to broadcast messages
     * through the specified groups
     * @author Lauren Brown
     * @version 2019.1.12
     * @license Apache License 2.0
     */

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <netdb.h>
#include "headers/DieWithError.h"
#include "headers/SystemLogger.h"
#include "headers/clear.h"

#define MAXRECVSTRING 255  /* Longest string to receive */

int connection;                         /* Socket */
struct sockaddr_in BroadcastGroup;
char recvString[MAXRECVSTRING+1]; /* Buffer for received string */
int recvStringLen;                /* Length of received string */
struct hostent *client;

void Config(u_int16_t portnum) {
    
    /// Setup a new connection ///
    if ((connection = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        DieWithError("socket() failed");
        Logger("BroadcastReciever_error.log", "socket() failed \n");
    }

    /// Create the network structure ///
    memset(&BroadcastGroup, 0, sizeof(BroadcastGroup));   /* Zero out structure */
    BroadcastGroup.sin_family = AF_INET;                 /* Internet address family */
    BroadcastGroup.sin_addr.s_addr = htons(INADDR_ANY);  /* Any incoming interface */
    BroadcastGroup.sin_port = htons(portnum);      /* Broadcast port */

    /* Bind to the broadcast port */
    if (bind(connection, (struct sockaddr *) &BroadcastGroup, sizeof(BroadcastGroup)) < 0) {
        DieWithError("bind() failed");
        Logger("BroadcastReciever_error.log", "bind() failed \n");
    }

    clear();
    printf("********* Broadcast Receiver ********* \n");
    printf("\n Listening for messages... \n");

    /* Receive a single datagram from the server */
    if ((recvStringLen = recvfrom(connection, recvString, MAXRECVSTRING, 0, NULL, 0)) < 0) {
        DieWithError("recvfrom() failed");
        Logger("BroadcastReciever_error.log", "recvfrom() failed \n");
    }

    recvString[recvStringLen] = '\0';
    clear(); // Clear the screen once a message is received from the server
    printf("Message Received: %s\n", recvString);    /* Print the received string */

    printf(" \n Connection closed");
    close(connection);
    exit(0);
}

int main(int argc, char *argv[])
{
    /// Run the client on port 6060 using any available network interface //
    Config(6060);

}