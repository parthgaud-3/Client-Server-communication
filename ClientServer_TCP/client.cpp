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
    
    if(argc != 3){
        cerr<<"Missing hostname and port number"<<endl;
        exit(0);
    }

    char *serverName = argv[1];
    int port = atoi(argv[2]);

    char message[1500];

    //retrieve host details and declare client socket
    struct hostent* host = gethostbyname(serverName);

    struct sockaddr_in clientSocket;
    clientSocket.sin_family = AF_INET;
    clientSocket.sin_port = htons(port);
    clientSocket.sin_addr = **(struct in_addr **)host->h_addr_list;

    //socket() call to get file descripter

    int clientSocketID = socket(AF_INET, SOCK_STREAM, 0);

    //connect() to the remote address

    int status = connect(clientSocketID, (struct sockaddr *)&clientSocket, sizeof(clientSocket));
    if(status < 0){
        cerr<<"Error Connecting!"<<endl;
        exit(0);
    }
    cout<<"Successful Connection!"<<endl;

    //message transfer

    while(true){

        string data;
        cout<<"Client: ";
        getline(cin,data);
        strcpy(message,data.c_str());
        if(data == "exit"){
            cout<<"Connection terminated"<<endl;
            break;
        }
        send(clientSocketID,message,sizeof(message),0);

        cout<<"Server :";
        recv(clientSocketID,message,sizeof(message),0);
        if(!strcmp(message, " exit")){
            cout<<"Connection terminated"<<endl;
            break;
        }
        cout<<message;
    }
    close(clientSocketID);

}
