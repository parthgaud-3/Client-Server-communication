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

int main(int argc, char *argv[]){

    if(argc != 2){
        cerr<< "Missing Port number"<<endl;
        exit(0);
    }
    int port = atoi(argv[1]);
    char message[1500];
    
    //define sockaddr_in

    struct sockaddr_in serverSocket;
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(port);
    serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);

    int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSocketID < 0){
        cerr<<"Not successful"<<endl;
        exit(0);
    }
    // bind the socket with port
    int bindStatus = bind(serverSocketID, (struct sockaddr*) &serverSocket, sizeof(serverSocket));

    if(bindStatus < 0){
        cerr<<"Not successful bind"<<endl;
        exit(0);
    }

    cout<<"Waiting for client to connect..."<<endl;

    //listen() for client calls

    listen(serverSocketID,1);

    struct sockaddr_in newSocket;
    socklen_t newSocketlen = sizeof(newSocket);

    // accepting client call and declaring separate socket

    int newSocketID = accept(serverSocketID, (sockaddr *) &newSocket, &newSocketlen);

    if(newSocketID < 0){
        cerr<<"Not succesful accept() \n";
        exit(0);
    }

    cout<<"Client connected successfully\n";

    //Transfer of messages

    while(true){
        cout<<"Waiting for a message from clinet\n";
        recv(newSocketID,(char *)&message, sizeof(message),0);
        if(!strcmp(message, "exit")){
            cout<<"Session terminated";
            break;
        }
        cout<<message<<endl;
        string data;
        getline(cin,data);
        strcpy(message,data.c_str());
        if(data == "exit"){
            cerr<<"Session Terminated";
            exit(0);
        }
        send(newSocketID,(char *)&message, sizeof(message),0);
    }
    close(newSocketID);
    close(serverSocketID);

}
