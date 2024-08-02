#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "student.h"
#include "writer.h"

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "-input") != 0)
    {
        fprintf(stderr, "Invalid arguments. Usage: %s -input <input_file>\n", argv[0]);
        return 1;
    }
    char *inputFile = (char *)malloc(strlen(argv[2]) + 1);
    char *outputFile = "2108_2119.out";
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