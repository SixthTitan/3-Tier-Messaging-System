/**
     * Mutlibroadcaster
     * This Client / Server package is designed to broadcast messages
     * through the specified groups
     * @author Lauren Brown
     * @version 2019.1.12
     * @license Apache License 2.0
     */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <netdb.h>
#include "headers/DieWithError.h"
#include "headers/clear.h"
#include "headers/SystemLogger.h"

#define MAXRECVSTRING 255  /* Longest string to receive */

struct sockaddr_in LoopbackInterface;
struct ip_mreq group;
int msgsize;
char message [MAXRECVSTRING+1];
struct hostent *client;

void Config(char ipaddress[10], u_int16_t portnum) {

    int reuse = 1;

    client = gethostbyname(ipaddress); // Resolve hostname to ip address if hostname is given
    char * hostname = client->h_addr; // Store the pointer with the ip address to a variable

    /// Setup a new connection ///
    int connection = socket(AF_INET, SOCK_DGRAM, 0); // Create a new datagram connection

    if (connection < 0) { // Did the connection fail?
        DieWithError("Error: Cannot open datagram socket, please try again \n");
        Logger("error.log", "Error: Cannot open datagram socket, please try again \n");
        exit(1);
    }
    else {
        clear();
        printf("******** Setup ******** \n \n");
        printf("1. Opening datagram socket... \n");
    }

    /// allow multiple copies of the client in order to recieve copies of the multicast datagram
    if(setsockopt(connection, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0) {

        DieWithError("Setting SO_REUSEADDR error \n");
        Logger("error.log", "Setting SO_REUSEADDR error \n");
        close(connection);
        exit(1);
    }

    else printf("2. Setting up REUSE Address Successful .\n");


    /// Create the network structure ///
    memset((char *) &LoopbackInterface, 0, sizeof(LoopbackInterface));
    LoopbackInterface.sin_family = AF_INET;
    LoopbackInterface.sin_port = htons(portnum);
    memmove((char *) &LoopbackInterface.sin_addr.s_addr, client->h_addr, client->h_length);

    if(bind(connection, (struct sockaddr*)&LoopbackInterface, sizeof(LoopbackInterface)))

    {
        DieWithError("Binding datagram socket error \n");
        Logger("error.log", "Binding datagram socket error \n");
        close(connection);
        exit(1);
    }

    else printf("3. Binding datagram socket...OK.\n");


    /* Join the multicast group 224.0.0.1 on the local 127.0.0.1 */
    /* interface. Note that this IP_ADD_MEMBERSHIP option must be */
    /* called for each local interface over which the multicast */
    /* datagrams are to be received. */
    group.imr_multiaddr.s_addr = inet_addr(hostname);
    group.imr_interface.s_addr = htonl(INADDR_ANY);

    if(setsockopt(connection, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&group, sizeof(group)) < 0)

    {

        DieWithError("Adding multicast group error");
        Logger("error.log", "Adding multicast group error \n");
        close(connection);
        exit(1);

    }

    else {
        printf("4. Adding multicast group...OK.\n \n");
        clear();

        printf("********* Multicast Receiver ********* \n");
        printf("\n Listening for messages... \n");
    }



    /* Receive a single datagram from the server */
    if ((msgsize = recvfrom(connection, message, MAXRECVSTRING, 0, NULL, 0)) < 0)
        DieWithError("recvfrom() failed \n");

    message[msgsize] = '\0';
    printf("Message Received: %s\n", message);    /* Print the received string */

}

int main (int argc, char *argv[ ]) {

    /// Run the client on localhost with port 6060 using any available network interface //
    Config("localhost", 6060);
    return 0;
}
