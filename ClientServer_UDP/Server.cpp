#include <sys/types.h>             
#include <sys/socket.h> 
#include <netinet/in.h>                                                                                                               
#include <arpa/inet.h>                                                                                                                
#include <unistd.h>                                                                                                                   
#include <netdb.h>                                                                                                                    
#include <sys/time.h>                                                                                                                 
#include <sys/wait.h>
#include<bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
    // check for port number passed as argument
    if (argc != 2)
    {
        perror("Missing port number\n");
        exit(EXIT_FAILURE);
    }
    int port = atoi(argv[1]);
    // buffer to store sent and recieved messages
    char message[1500];

    // define a sockaddr_in struct for socket server (the socket listening)
    struct sockaddr_in serverSocket;
    serverSocket.sin_family = AF_INET; // IPV4 addresses
    serverSocket.sin_port = htons(port);
    serverSocket.sin_addr.s_addr = htonl(INADDR_ANY); // server socket can listen to any interface

    // socket() for server socket
    // int socketID = socket(Family, Type, Protocol)
    int serverSocketID = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocketID == 0)
    {
        perror("Socket failure\n");
        exit(EXIT_FAILURE);
    }

    // bind() the socket to a port
    // int status = bind(socketID, &addressPort, sizeOfPort)
    int bindStatus = bind(serverSocketID, (struct sockaddr *)&serverSocket, sizeof(serverSocket));
    if (bindStatus < 0)
    {
        perror("Bind failure\n");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in clientSocket;

    while (true)
    {
        socklen_t addrlen = sizeof(clientSocket);
        int status = recvfrom(serverSocketID, (char *)&message, sizeof(message), 0, (struct sockaddr *) &clientSocket, &addrlen);
        if (!strcmp(message, "EXIT"))
        {
            printf("Session terminated\n");
            break;
        }
        printf("Client: %s\nHost: ", message);
        char messageToClient[1500];
        scanf("%s", messageToClient);
        sendto(serverSocketID, (char *)&messageToClient, sizeof(messageToClient), 0, (struct sockaddr *)&clientSocket, addrlen);
        if (!strcmp(messageToClient, "EXIT"))
        {
            printf("Session terminated\n");
            break;
        }
    }

    // close() the socket and free the bound port
    // int status = close(socketID)
    close(serverSocketID);
}
