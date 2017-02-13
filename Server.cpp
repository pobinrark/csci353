/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     bool isExit = true;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
    cout << "Connection made with client" << endl;
    cout << "Type 'EXIT' to close connection" << endl;
    char key[] = "EXIT";
    char exitMsg[] = "Server has disconnected";
    while(true)
    {
        //send(newsockfd, "Server: Connection made with server", 256, 0);
        bzero(buffer, 256);
        
        //chatting part
        recv(newsockfd, buffer, 255, 0);
        cout << "register: " << buffer << endl;
        cout << "welcome: ";
        cin >> buffer;
        if(strcmp(buffer, key) == 0)
        {
        	cout << "Exiting" << endl;
        	send(newsockfd, exitMsg, strlen(exitMsg), 0);
        	break;
        }
        send(newsockfd, buffer, 255, 0);
        cout << endl;
        
        //cout << "Closing connection" << endl;
        //inet_ntoa(serv_addr.sin_addr);
        //exit(1);
    }
     close(newsockfd);
     close(sockfd);
     return 0; 
}
