#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "student.h"
#include "writer.h"

StudentNode *studentHead = NULL;
char logMessage[200];

int main(int argc,char* argv[]){
    char *inputFile = (char*)malloc(strlen(argv[2]) + 1);
    char *outputFile = "08_19.out";
    if (inputFile == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(inputFile, argv[2]);
    initParse(inputFile);
    initWrite(outputFile);

    free(inputFile);

    return 0;
}