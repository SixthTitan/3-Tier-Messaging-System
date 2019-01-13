/**
     * Error Logging Header
     * This provides source files with the ability to print an error to a log file in the project directory
     * without having to add it in the actual source file, one can simply include this header and make the system call
     * @author Lauren Brown
     * @version 2019.1.13
     * @license See the included LICENSE.txt file for more information.
     */

#ifndef PROJECT2_SYSTEMLOGGER_H
#define PROJECT2_SYSTEMLOGGER_H

#include <stdio.h>
#include <time.h>

/// Logging file handler
void Logger(char * filename, char * data) {
    FILE *logfile;
    logfile = fopen(filename, "a+");
    fprintf(logfile, data);
    fclose(logfile);
}

#endif //PROJECT2_SYSTEMLOGGER_H
