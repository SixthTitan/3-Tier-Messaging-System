Project 2

-- Documentation 
---- includes project requirements and this readme file

-- Headers
---- includes the required header files in which the programs depend on in order to perform their required functionality

-- Screenshots
---- includes images of the running application

-- Third-Party
---- includes Rawcap utility which enables you to capture packets from a Loopback Adapter on a Windows Machine


--- Programs ---
Application: This is the main application that allows a user to select from a variety of options and run the complied programs from an easy to understand command line UI

Broadcast Reciever: this application will recieve an incoming broadcast message from the Broadcast Server and can be configured by Config("port number of Broadcast server goes here"); 

Broadcast Sender: this application will send out a message to the Broadcast reciever and can be configured by Config("Hostname or IP Address", "port number", "Message to send");

Multicast Reciever: this application will recieve an incoming multicast message from the multicast Server and can be configured by Config("port number of Broadcast server goes here"); 
Note: it's currently configured to send / recieve messages from the same machine, to send / recieve messages from to different machines; replace IP_MULTICAST_LOOP with IP_ADD_MEMBERSHIP on line 71

Multicast Sender: this application will send out a message to the Broadcast reciever and can be configured by Config("Hostname or IP Address", "port number", "Message to send");
Note: it's currently configured to send / recieve messages from the same machine, to send / recieve messages from to different machines; replace IP_MULTICAST_LOOP with IP_MULTICAST_IF on line 71


Getting started:
1. run Make -f Makeapp to compile Application.o
2. execute ./Application.o
3. Select option 0, Pre-Install Dependencies to compile the multicast and broadcast programs
4. Run either the Broadcast Sender or the Multicast Sender or both the program will stay open and continue to send messages until you press CTRL + C
5. Run either Broadcast Reciever or Multicast Reciever or both to get the sent message. 

Note: The message sent for Broadcast and Multicast are different.

Error Logging:
Any errors that occur will output to the console and also to a log file, the log file is created in the root project directory and will be named programname_error.log, the programname is the name of the program that you
had run which encountered an error, it will append a new line if a file already exists, you'll need to delete this file eventually if it becomes too big.


Main goals:

DONE Incorporate user input
DONE incorporate Multicast and Broadcast communication techniques
DONE incorporate name and service resolution
Note: I couldn't make both name and service resolution work due to the way I had my program setup, so only name resolution works.

incorporate daemon/background concepts
Note: This couldn't be accomplished because I wasn't using user arguments, I was merely passing them into a function named Config, I did attempt it however but it just couldn't be done because of the way I had
written this program, but It is running in the background with a keeprunning while loop, it's just not in a daemon.

I tried: DaemonInit(Config("localhost", 6060, "Starbucks", 0); and set my function Config to a constant char, but I ran into a lot of errors.

DONE implement signal catching to make your background/daemon processes more resilient
DONE utilize messaging with Syslog for applications components in the background.

