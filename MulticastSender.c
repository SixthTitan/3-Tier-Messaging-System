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
struct sockaddr_in MulticastGroup;
struct hostent *server;
struct sysinfo info;
char * hostname;

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

    unsigned int msgsize = sizeof(message);

    server = gethostbyname(ipaddress); // Resolve hostname to ip address if hostname is given
    hostname = server->h_addr; // Store the pointer with the ip address to a variable

    /// Setup a new connection ///
    int connection = socket(AF_INET, SOCK_DGRAM, 0); // Create a new datagram connection

    if (connection < 0) { // Did the connection fail?
        DieWithError("Error: Cannot open datagram socket, please try again \n");
        Logger("error.log", "Error: Cannot open datagram socket, please try again \n");
        exit(1);
    }
    else printf("Opening new datagram socket... \n");

    /// Create the network structure ///
    memset((char *) &MulticastGroup, 0, sizeof(MulticastGroup));
    MulticastGroup.sin_family = AF_INET; // Our address family
    memmove((char *) &MulticastGroup.sin_addr.s_addr, server->h_addr, server->h_length);
    MulticastGroup.sin_port = htons(portnum); // Our Port Number

    /// Setup the Loopback address to send outbound multicast datagrams
    LoopbackInterface.s_addr = inet_addr(hostname); // Our Ip Address
    if (setsockopt(connection, IPPROTO_IP, IP_MULTICAST_LOOP, (char * ) &LoopbackInterface, sizeof(LoopbackInterface)) < 0)
    {
    DieWithError("Error: Unable to create a local network interface \n");
    Logger("error.log", "Error: Unable to create a local network interface \n");
    exit(1);

    }

    else printf("Setting up the local network interface \n");

    /// Send out a message to the world ///
    if(sendto(connection, message, msgsize, 0, (struct sockaddr*) &MulticastGroup, sizeof(MulticastGroup)) < 0 )
    {
        DieWithError("Unable to send the datagram message \n");
        Logger("error.log", "Unable to send the datagram message \n");
    }

    else {
        clear(); // Clear the Screen
        printf("****** Server Started ****** \n");

        /// Create a new Signal handler
        signal(SIGINT, intHandler);

        /// Make a one-time annoucement and then keep sending the message until CTRL + C is entered
        while(keepRunning) {
                sendto(connection, message, msgsize, 0, (struct sockaddr*) &MulticastGroup, sizeof(MulticastGroup));
                sleep(15); // Prevent excessive CPU usage by only sending the message every 15 seconds
        }

    }

};


int main (int argc, char *argv[ ]) {

    /// Run a Multicast with the specified arguments ///
    Config("localhost", 6060, "Starbucks");
}
