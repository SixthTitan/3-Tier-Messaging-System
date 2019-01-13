/**
     * System Dependent Macro Clear Console Screen Handler
     * This provides source files with the ability to clear the console screen on Windows or Linux
     * without having to add it in the actual source file, one can simply include this header and make the system call
     * @author Lauren Brown
     * @version 2018.11.30
     * @license See the included LICENSE.txt file for more information.
     */

#ifndef PROJECT1_CLEAR_H
#define PROJECT1_CLEAR_H

void clear(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

#endif //PROJECT1_CLEAR_H
