/**
     * Multicast / Broadcast Sender and Reciever
     * This Client / Server package is designed to communicate with each other
     * It is a simple program to show how the server and client talk to each other over a network
     * @author Lauren Brown
     * @version 2019.1.13
     * @license See the included LICENSE.txt file for more information.
     */

/** System Headers */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>


/** Custom Headers */
#include "headers/clock.h" // Our Time / Date Handler
#include "headers/clear.h" // Our Console Screen Clear Handler
#include "headers/DieWithError.h" // Our Error Handler


/** Code Snippets
 * CaesarCipher(1, "test"); // 1 is Encrypt
 * CaesarCipher(2, "test"); //2 is Decrypt
 * DieWithError("Error");
 * fileOpen("Quote_File.txt", output, "r"); // "Filename to read", variable to save text to, file mode
 * clockwatch(0-3); //Display current date and time
 * 0 = Local time only, 1 = Date only, 2 = GMT with date, 3 = Local Time with Date
 * intro(); // Display current date and time with introduction menu option
 * clear(); //Clear the screen for Windows and or Linux Systems
 * */

void intro() {

    printf("\n Welcome to Lauren's Multicast/Broadcast System \n");

    printf("***********************************************\n");

    clockwatch(0); // Print today's time and date here


    printf("\n To get started, please select from the following options \n \n");

    printf("\n 0. Pre-Install Dependencies ");
    printf("\n 1. Start Multicast Server ");
    printf("\n 2. Start Multicast Receiver ");
    printf("\n 3. Start Broadcast Server");
    printf("\n 4. Start Broadcast Receiver \n");
    printf("\n 5. Exit \n");

    int testInteger;
    int systat;

    printf("\n Enter an option: ");
    scanf("%d", &testInteger);


    switch (testInteger) {
        case 0:
            //Pre-Install Dependencies Selected
            printf("\n ");
            systat = system("make");

            if (systat == -1) {
                DieWithError("Error: Makefile not found or Make is not installed.");
                break;
            }

            else {
                exit(1);

            }


        case 1:
            ///Multicast Server selected
            system("./MulticastSender.o"); //Execute and run the compiled program
            break;

        case 2:
            /// Mutlicast Reciever Selected
            system("./MulticastReciever.o"); //Execute and run the compiled program
            break;

        case 3:
            /// Broadcast Sender Selected
            system("./BroadcastSender.o"); //Execute and run the compiled program
            break;

        case 4:
            /// Broadcast Reciever Selected
            system("./BroadcastReceiver.o"); //Execute and run the compiled program
            break;

        case 5:
            // Quit Selected
            exit(1); // Quit

        default:
            clear();
            intro();
    }


}



int main(void) {

    intro(); // Run the introduction function

    return 0;
}
