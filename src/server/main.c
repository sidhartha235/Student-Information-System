#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <netinet/in.h>

#include "server.h"

int main(int argc, char **argv) {
    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: ./server_08_19 <serv_port>\n");
        exit(1);
    }

    uint16_t serv_port = atoi(argv[1]);
    if (serv_port <= 0) {
        fprintf(stderr, "Invalid port number!\n");
        exit(1);
    }

    int listenfd = initializeServer(htons(serv_port));
    printf("Server started on port %d\n", serv_port);
    printf("Listening for connections...\n");

    runServer(listenfd);
    
    stopServer(listenfd);
    
    return 0;
}