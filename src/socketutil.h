#ifndef SOCKETUTIL_H
#define SOCKETUTIL_H

#include <sys/socket.h> // definitions for socket structures
#include <netinet/in.h> // contains definitiosn for internet domain addresses
#include <arpa/inet.h>
#include <malloc.h>

int CreateIpv4Socket();
struct sockaddr_in* CreateIpv4Address(char* ip_address, int port);

#endif