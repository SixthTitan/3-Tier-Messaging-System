/**
     * Error Handling Header
     * This provides source files with the ability to display an error
     * without having to add it in the actual source file, one can simply include this header and make the system call
     * @author Lauren Brown
     * @version 2018.11.30
     * @license See the included LICENSE.txt file for more information.
     */

#ifndef PROJECT1_DIEWITHERROR_H
#define PROJECT1_DIEWITHERROR_H

#include <stdlib.h>
#include <stdio.h>

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

#endif //PROJECT1_DIEWITHERROR_H
