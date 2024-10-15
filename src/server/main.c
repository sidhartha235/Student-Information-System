#include <stdio.h>
#include <unistd.h>

#include "server.h"
#include "fifo.h"

int main() {
    printf("Starting server...\n");

    makeFifo();

    readFromFifo();
    
    unlink(FIFO);
    
    return 0;
}