#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h> // contains data types for sys calls
#include <stdbool.h>
#include <pthread.h>

#include "socketutil.h"
#include "helper.h"

#define MAXBUF 1024 /*max line limit for message*/

struct client {
    int sockFD;
    struct sockaddr_in address;
    bool connected;
    int error;
};
void handleIncomingConnection(int serverSocketFD);
struct client* accpetIncomingConnection(int serversocketFD);
void reader(struct client* client);


#endif