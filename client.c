/*
	Simple winsock client 
*/
// Joel- 25.62.238.210
// Duarte- 25.67.232.65
// Bruno- 25.68.99.102

#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable : 4996)

int main(int argc, char *argv[])
{
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	char *message, server_reply[2000];
	int recv_size;
	int ws_result;
	


	// Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//Create a socket
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");

	// create the socket  address (ip address and port)
	server.sin_addr.s_addr = inet_addr("25.62.238.210");
	server.sin_family = AF_INET;
	server.sin_port = htons(68000);

	//Connect to remote server
	ws_result=connect(s, (struct sockaddr *)&server, sizeof(server));
	if (ws_result < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");

	//Send some data
	message = "GET / HTTP/1.1\r\n\r\n";
	ws_result = send(s, message, strlen(message), 0);
	if (ws_result < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Sent\n");
	

	//Receive a reply from the server
	recv_size = recv(s, server_reply, 2000, 0);
	if (recv_size == SOCKET_ERROR)
	{
		puts("recv failed");
	}

	puts("Reply received\n");

	//Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	puts(server_reply);
	


	//Cleanup winsock
	WSACleanup();

	return 0;
}
