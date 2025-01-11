#include <stdio.h> // for IO operations
#include <stdlib.h>  // contains various types, macros and functions
#include <string.h> 
#include <unistd.h>
#include <sys/types.h> // contains data types for sys calls
#include <errno.h>
#include <stdbool.h>

#include "socketutil.h"



int main() {
    int serverSocketFD = CreateIpv4Socket();
    struct sockaddr_in *serverAddress = CreateIpv4Address("", 3331);

    int result = bind(serverSocketFD, serverAddress, sizeof(*serverAddress));
    if (result == 0) {
        printf("socket was bound successfully\n");
    } else {
        printf("error while binding socket\n");
    }
    
    // the amount of active connections to listen to
    int count = 10;
    listen(serverSocketFD, count);
    struct sockaddr_in *clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    int clientSocketFD = accept(serverSocketFD, &clientAddress, clientAddressSize);

    char buffer[1024];
    
    while(true) {
        ssize_t amountRecieved = recv(clientSocketFD, buffer, 1024, 0);

        if (amountRecieved > 0) {
            // insert null termination to the end of the message
            buffer[amountRecieved] = 0;
            printf("%s\n", buffer);
        }

        if (amountRecieved == 0) {
            break;
        }
    }

    close(clientSocketFD);
    shutdown(serverSocketFD, SHUT_RDWR);
    return 0;
}