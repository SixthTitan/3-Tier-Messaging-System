/**
     * BroadcastSender
     * This Client / Server package is designed to broadcast messages
     * through the specified groups
     * @author Lauren Brown
     * @version 2019.1.12
     * @license Apache License 2.0
     */

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <netdb.h>
#include <cygwin/signal.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include "headers/DieWithError.h"
#include "headers/clear.h"
#include "headers/SystemLogger.h"


/// Our Variables
struct in_addr LoopbackInterface;
struct sockaddr_in BroadcastGroup;
struct hostent *server;
struct sysinfo info;
int broadcastPermission;          /* Socket opt to set permission to broadcast */
unsigned int msgsize;

bool volatile keepRunning = true; // Used to terminate the endless loop via user input

/// Signal Handler for CTRL + C
void intHandler(int dummy) {
    keepRunning = false;
    clear();

    /// Display total time the service was running ///
    printf("****** Server Stopped ****** \n \n");
    sysinfo(&info);
    printf("Uptime (secs): %02ld \n", info.uptime%60);
}

void Config(char ipaddress[10], u_int16_t portnum, char *message) {


    server = gethostbyname(ipaddress); // Resolve hostname to ip address if hostname is given
    char * hostname = server->h_addr; // Store the pointer with the ip address to a variable

    /// Setup a new connection ///
    int connection = socket(PF_INET, SOCK_DGRAM, 0); // Create a new datagram connection

    if (connection < 0) { // Did the connection fail?
        DieWithError("Error: Cannot open datagram socket, please try again \n");
        Logger("broadcast_error.log", "Error: Cannot open datagram socket, please try again \n");
        exit(1);
    }
    else printf("Opening new datagram socket... \n");

    /// Create the network structure ///
    memset((char *) &BroadcastGroup, 0, sizeof(BroadcastGroup));
    BroadcastGroup.sin_family = AF_INET; // Our address family
    BroadcastGroup.sin_addr.s_addr = inet_addr(hostname);/* Broadcast IP address */
    BroadcastGroup.sin_port = htons(portnum); // Our Port Number

    msgsize = strlen(message);

/* Set socket to allow broadcast */
    broadcastPermission = 1;
    if (setsockopt(connection, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,
                   sizeof(broadcastPermission)) < 0) {
        DieWithError("setsockopt() failed \n");
        Logger("broadcast_error.log", "setsockopt() failed \n");
    }

    else {
        clear(); // Clear the Screen
        printf("****** Server Started ****** \n");

        /// Create a new Signal handler
        signal(SIGINT, intHandler);

        /// Make a one-time annoucement and then keep sending the message until CTRL + C is entered
        while(keepRunning) {
            sendto(connection, message, msgsize, 0, (struct sockaddr*) &BroadcastGroup, sizeof(BroadcastGroup));
            sleep(15); // Prevent excessive CPU usage by only sending the message every 15 seconds
        }

    }

};

int main(int argc, char *argv[])
{
    /// Run a Broadcast with the specified arguments ///
    Config("localhost", 6060, "Mocha is the best!");
}
