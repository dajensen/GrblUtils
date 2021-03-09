#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <alloca.h>


void die(const char *format, ...) {
    va_list ap;

    printf("\n***********************************************\n");
    printf("                 TEST FAILED                   \n");
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
    printf("\n***********************************************\n");
    printf("\n");
    exit(-1);
}

int main(int argc, char *argv[]){

    printf("\nAll is well\n");
}

