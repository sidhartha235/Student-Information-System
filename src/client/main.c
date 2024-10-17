#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "client.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    if (argc != 5 || strcmp(argv[3], "-input") != 0)
    {
        fprintf(stderr, "Invalid arguments. Usage: %s <SERVER_ADDR> <SERVER_PORT> -input <input_file>\n", argv[0]);
        exit(2);
    }
    char *inputFile = (char *)malloc(strlen(argv[4]) + 1);
    char *serv_addr = (char *)malloc(strlen(argv[1]) + 1);
    int port = atoi(argv[2]);
    if (inputFile == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(2);
    }
    strcpy(serv_addr, argv[1]);
    if (strcmp(serv_addr, "") == 0)
    { // Other edge cases handled in inet_pton
        fprintf(stderr, "Invalid server address\n");
        exit(2);
    }
    if (port <= 0)
    {
        fprintf(stderr, "Invalid port number\n");
        exit(2);
    }
    strcpy(inputFile, argv[4]);
    printf("Input file: %s\n", inputFile);
    printf("Server address: %s\n", serv_addr);
    printf("Port: %d\n", port);

    openConnection(serv_addr, port);
    initParse(inputFile);
    closeConnection();

    free(inputFile);
    free(serv_addr);

    return 0;
}