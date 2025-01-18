# Chatroom-server
Chatroom is a C only, linux native chatroom based on TCP/IP server-client model.

Clients dispatch messages through Linux sockets and server listens to its port and upon receiving a new message, responds by sending the message to other clients that are currently connected to the server.

# Building and running the project
### With CMake
Run the following command
   ```
   cmake -B ./build
   cmake --build build
   ./build/src/server
   ```
