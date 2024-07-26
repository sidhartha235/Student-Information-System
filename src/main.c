#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

int main(int argc,char* argv[]){
    char *inputFile = (char*)malloc(strlen(argv[2]) + 1);
    if (inputFile == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(inputFile, argv[2]);
    initParse(inputFile);

    return 0;
}


