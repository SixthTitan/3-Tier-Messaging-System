/**
     * Time / Date Handler
     * This provides source files with the ability to print the current time and date to console
     * without having to add it in the actual source file, one can simply include this header and make the system call
     * @author Lauren Brown
     * @version 2018.11.30
     * @license See the included LICENSE.txt file for more information.
     */

#ifndef PROJECT1_CLOCK_H
#define PROJECT1_CLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tm *ptr;             //structure to pull discreet portions of the time_date
int hour;
char am_or_pm;

void clockwatch(int const format) {
    time_t current = time(NULL);

    /** Use Time only in Local Format if 0 is used */
    if (format == 0) {

        for (int i = 0; i < 1; i++) {

            ptr = localtime(&current);  // local time format pulled
            i++;
        }

        hour = ptr->tm_hour;
        if (hour < 11)
            am_or_pm = 'a';
        else {
            hour -= 12;
            am_or_pm = 'p';
        }
        if (hour == 0)
            hour = 12;
        puts("\n Current Time: ");
        printf(" %2d:%2d%c\n",  hour, ptr->tm_min,
               am_or_pm);
    }

    /** Use Date only if 1 is used */
    if (format == 1) {

        for (int i = 0; i < 1; i++) {

            ptr = localtime(&current);  // local time format pulled
            i++;
        }

        hour = ptr->tm_hour;
        if (hour < 11)
            am_or_pm = 'a';
        else {
            hour -= 12;
            am_or_pm = 'p';
        }
        if (hour == 0)
            hour = 12;
        puts("\n Today's Date: ");
        printf(" %.2d-%.2d-%d \n", ptr->tm_mon + 1, ptr->tm_mday, ptr->tm_year + 1900);
    }

    /** Use GMT Format if 2 is used */
    if (format == 2) {

        for (int i = 0; i < 30; i++) {


            ptr = gmtime(&current);   // gmt time format pulled
            hour = ptr->tm_hour;
            if (hour < 11)
                am_or_pm = 'a';
            else {
                hour -= 12;
                am_or_pm = 'p';
            }
            if (hour == 0)
                hour = 12;
        }
        puts("GMT Time:");
        printf("%.2d-%.2d-%d %2d:%2d%c\n", ptr->tm_mon + 1, ptr->tm_mday, ptr->tm_year + 1900, hour, ptr->tm_min,
               am_or_pm);
    }


    /** Use Local Time Format with Date if 3 is used */
    if (format == 3) {

        for (int i = 0; i < 30; i++) {

            ptr = localtime(&current);  // local time format pulled
            hour = ptr->tm_hour;
            if (hour < 11)
                am_or_pm = 'a';
            else {
                hour -= 12;
                am_or_pm = 'p';
            }
            if (hour == 0)
                hour = 12;

            i++; // Increment and update time every 30 seconds

        }

        puts("Local Time:");
        printf("%.2d-%.2d-%d %2d:%2d%c\n", ptr->tm_mon + 1, ptr->tm_mday, ptr->tm_year + 1900, hour, ptr->tm_min,
               am_or_pm);
    }
}


#endif //PROJECT1_CLOCK_H
