#include "enum.h"

int initializeServer(uint16_t serv_port);
void runServer(int listenfd);
void stopServer(int listenfd);
void updateDB(int connfd);
void extractData(Operation operation, void *data);