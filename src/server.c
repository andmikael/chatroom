#include "server.h"

int main() {
    int serverSocketFD = CreateIpv4Socket();
    struct sockaddr_in *serverAddress = CreateIpv4Address("", 6633);

    int result = bind(serverSocketFD, serverAddress, sizeof(*serverAddress));
    if (result == 0) {
        printf("socket was bound successfully\n");
    } else {
        printf("error while binding socket\n");
        return 0;
    }
    
    // the amount of active connections to listen to
    int count = 10;
    listen(serverSocketFD, count);

    // create a listener thread for incoming messages


    char buffer[MAXBUF];	//Temporary buffer to read and write data

       while(1){
        handleIncomingConnection(serverSocketFD);
       //read the command
        /*if ((fgets(buffer, MAXBUF, stdin) == NULL) && ferror(stdin)) {
            perror("fgets error");
            break;
        }

      // send the request to the server
      if (rio_writen(user->sockFD,buffer,strlen(buffer)) == -1){
          perror("not able to send the data");
          break;
        }*/

    }
    return 0;
}

void handleIncomingConnection(int serverSocketFD) {
    pthread_t pid;
    struct client* user = accpetIncomingConnection(serverSocketFD);
    pthread_create(&pid,NULL, reader, (void*) user);
    pthread_detach(pthread_self());

}

// accept and incoming connection and return a client struct
struct client* accpetIncomingConnection(int serverSocketFD) {
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, &clientAddress, &clientAddressSize);

    struct client* clientSocket = malloc(sizeof(struct client));
    clientSocket->address = clientAddress;
    clientSocket->sockFD = clientSocketFD;
    clientSocket->connected = clientSocketFD > 0;
    if (!clientSocket->connected) {
        clientSocket->error = clientSocketFD;
    }

    printf("new user joined\n");
    return clientSocket;
}

// free allocated memory when user quits chatroom
void deleteUser(struct client* user) {
    free(user);
}

// read client response
void reader(struct client* client) {
    char buf[MAXBUF];
    rio_t rio;
    int status;
    int connID=client->sockFD;

    // init buffers for client socket
    rio_readinitb(&rio, connID);

    while(1) {
        // read a buffered line 
        while((status=rio_readlineb(&rio,buf,MAXBUF)) > 0) {
            //error
            if(status == -1)
                exit(1);
            if(!strcmp(buf,"\r\n")){
                break;
            }
            // exit from the server
            if (!strcmp(buf,"exit")){
                close(connID);
                deleteUser(client);
            }
            if (!strcmp(buf,"start\n")){
                printf("\n");
            } else {
                printf("%s",buf);
            }
        fflush(stdout);
        }
    }
}
