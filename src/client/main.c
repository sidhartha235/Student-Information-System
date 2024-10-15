#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "client.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "-input") != 0)
    {
        fprintf(stderr, "Invalid arguments. Usage: %s -input <input_file>\n", argv[0]);
        exit(2);
    }
    char *inputFile = (char *)malloc(strlen(argv[2]) + 1);
    if (inputFile == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(2);
    }


    strcpy(inputFile, argv[2]);
    if(openFifo() == 1)
        exit(1);
    initParse(inputFile);
    closeFifo();

    free(inputFile);

    return 0;
}