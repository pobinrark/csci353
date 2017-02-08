#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

int main()
{
	int client;
	int port;
	int buffsize = 1024;
	char buffer[buffsize];
	char* ip = "127.0.0.1";
	sockaddr_in server_addr;
	bool isExit;

	client = socket(AF_INET, SOCK_DGRAM, 0);
	if(client < 0)
	{
		cout << "Error creating socket" << endl;
		exit(1);
	}

	cout << "Socket has been created" << endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	if(connect(client,(sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		cout << "Connection error" << endl;
	}

	cout << "Connection success, connected to port: " << port << endl;
	cout << "Type EXIT to quit" << endl;

	while(isExit)
	{
		cout << "register: ";
		cin >> buffer;
		send(client, buffer, buffsize, 0);
		if(*buffer == 'EXIT')
		{
			isExit = false;
			break;
		}
		recv(client, buffer, buffsize, 0);
		cout << "welcome: " << buffer << endl;
	}

	cout << "Connection ended" << endl;
	close(client);




	return 0;
}