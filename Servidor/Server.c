/*
Simple winsock Server
*/

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#define TRUE 1
#define DS_TEST_PORT 68000

#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable : 4996)

int main()
{
	// Initialise winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	printf("\nInitialising Winsock...");
	int wsResult = WSAStartup(ver, &wsData);
	if (wsResult != 0) {
		fprintf(stderr, "\nWinsock setup fail! Error Code : %d\n", WSAGetLastError());
		return 1;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		fprintf(stderr, "\nSocket creationg fail! Error Code : %d\n", WSAGetLastError());
		return 1;
	}

	printf("\nSocket created.");

	// Bind the socket (ip address and port)
	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(DS_TEST_PORT);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (struct sockaddr*)&hint, sizeof(hint));

	// Setup the socket for listening
	listen(listening, SOMAXCONN);

	// Wait for connection
	struct sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (struct sockaddr*)&client, &clientSize);

	// Close listening socket
	// closesocket(listening);

	// Main program loop
	char strMsg[1024];
	char strRec[1024];
	ZeroMemory(strMsg, 1024);
	ZeroMemory(strRec, 1024);

	int i = 1;

	strcpy(strMsg, "\nHello! welcome to the server!\r\n\n");
	printf("\n%d : %s\n", strlen(strMsg), strMsg);

	// send(clientSocket, strMsg, strlen(strMsg), 0);

	while (TRUE) {

		ZeroMemory(strRec, 1024);
		ZeroMemory(strMsg, 1024);

		int bytesReceived = recv(clientSocket, strRec, 1024, 0);
		if (bytesReceived == SOCKET_ERROR) {
			printf("\nReceive error!\n");
			break;
		}
		if (bytesReceived == 0) {
			printf("\nClient disconnected!\n");
			SOCKET clientSocket = accept(listening, (struct sockaddr*)&client, &clientSize);
			// break;
		}

		printf("%i : received : %s\n", i, strRec);
		// send(clientSocket, strRec, bytesReceived, 0);

		if (strcmp(strRec, "teatros") == 0) {
			
			/*
			FILE* ptr;
			char ch;

			ptr = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Teatros.csv", "r");

			if (NULL == ptr)
			{
				printf("File cant be opened \n");
			}
			printf("Teatros: \n");

			do {
				ch = fgetc(ptr);
				printf("%c", ch);

				// Checking if character is not EOF.
				// If it is EOF stop eading.
			} while (ch != EOF);

			fclose(ptr);
			printf("Ficheiro fechado!\n");

			// Copiar a o conteudo do ficheiro para a string que se envia

			strcpy(strMsg, ch);
			send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
			
			*/

			// declare and initialise variable
			char ficheiro[256];
			char teste[256];
			int i = 0;

			FILE* file_in;
			file_in = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Teatros.csv", "r");

				while(!feof(file_in))
				{

				// stores and prints the data from the string
				fscanf(file_in, "%s", ficheiro);


				strcat(teste, ficheiro);
				strcat(teste, "/n");

				}
			// Copiar a o conteudo do ficheiro para a string que se envia
			strcpy(strMsg, ficheiro);
			
		
			send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
		}
		



		//  Funciona para abrir o ficheiro com o nome dos teatros.
		if (strcmp(strRec, "1") == 0) {
			
			// Substitute the full file path
			// for the string file_path
			FILE* fp = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Teatros.csv", "r");

			if (!fp)
				printf("Can't open file\n");

			else {
				// Here we have taken size of
				// array 1024 you can modify it
				char buffer[1024];

				int row = 0;
				int column = 0;

				while (fgets(buffer,
					1024, fp)) {
					column = 0;
					row++;

					// To avoid printing of column
					// names in file can be changed
					// according to need
					if (row == 1)
						continue;

					// Splitting the data
					char* value = strtok(buffer, ", ");

					while (value) {
						// Column 1
						if (column == 0) {
							printf("Name :");
						}

						// Column 2
						if (column == 1) {
							printf("\tAccount No. :");
						}

						// Column 3
						if (column == 2) {
							printf("\tAmount :");
						}

						printf("%s", value);
						value = strtok(NULL, ", ");
						column++;
					}

					printf("\n");
				}

				// Close the file
				fclose(fp);
			}


			send(clientSocket, strMsg, strlen(strMsg) +1, 0);

			

			// just to echo!
			// send(clientSocket, strRec, bytesReceived + 1, 0);
		}
		
		else if (strcmp(strRec, "ola") == 0) {

			strcpy(strMsg, "\nOla cliente\n");
			send(clientSocket, strMsg, strlen(strMsg) + 1, 0);

		}
		else if (strcmp(strRec, "date") == 0) {
			// current date/time based on current system
			time_t now = time(0);
			// convert now to string form
			char* dt = ctime(&now);

			strcpy(strMsg, "\nThe local date and time is: ");
			strcat(strMsg, dt);
			strcat(strMsg, "\n\n");

			send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
			

			// just to echo!
			// send(clientSocket, strRec, bytesReceived + 1, 0);
		}
		else if (strcmp(strRec, "bye") == 0) {

			strcpy(strMsg, "\nBye client...\n");
			send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
			break;
		}
		else{

			strcpy(strMsg, "\nNao enviaste nada\n\n");
			send(clientSocket, strMsg, strlen(strMsg) + 1, 0);

		}
		i++;
	}

	// Close the socket
	closesocket(clientSocket);

	//Cleanup winsock
	WSACleanup();
}