#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main()
{
	int client, server;
	int port = 1600;
	int buffsize = 1024;
	char buffer[buffsize];
	bool isExit;

	sockaddr_in server_addr;
	socklen_t size;

	//initialize socket;

	client = socket(AF_INET, SOCK_DGRAM, 0);

	if(client < 0)
	{
		cout << "Error establishing connection" << endl;
		exit(1);
	}
	cout << client << endl;
	cout << "Connection made!" << endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(port);

	if(bind(client, (sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		cout << "Error binding socket" << endl;
		exit(1);
	}	

	size = sizeof(server_addr);
	cout << "Looking for clients" << endl;

	//listening for client
	listen(client, 1);

	//accept client
	server = accept(client, (sockaddr*)&server_addr, &size);
	if(server < 0)
	{
		cout << "Error connecting to client" << endl;
		exit(1);
	}

	//connection made
	while(server > 0)
	{
		send(server, "Connection made with server", buffsize, 0);
		cout << "Connection made with client" << endl;
		cout << "Type 'EXIT' to close connection" << endl;
		
		//chatting part
		while(isExit)
		{
			cin >> buffer;
			if(*buffer == 'EXIT')
			{
				isExit = false;
				break;
			}
			cout << "welcome ";
			send(server, buffer, buffsize, 0);
			recv(server, buffer, buffsize, 0);
			cout << "register " << buffer << endl;

		}
		cout << "Closing connection" << endl;
		inet_ntoa(server_addr.sin_addr);
		close(server);
		exit(1);
	}
	close(client);
	return 0;
}