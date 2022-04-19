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
	int count = 0;
	int bilhetes = 0;
	char VisitouL[10];

	int i = 1;

	strcpy(strMsg, "\nHello! welcome to the server!\r\n\n");
	printf("\n%d : %s\n", strlen(strMsg), strMsg);

	// send(clientSocket, strMsg, strlen(strMsg), 0);


				// just to echo!
				// send(clientSocket, strRec, bytesReceived + 1, 0);

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





		if (strcmp(strRec, "teste") == 0) {


			char buffer[1024];

			FILE* file = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\teatros.txt", "r");
			// Checks if the file was opened successfully
			if (file == NULL)
			{
				fputs("Failed to open the file\n", stderr);
				return -1;
			}

			// fgets here reads an entire line or 99 characters (+1 for \0) at a time, whichever comes first
			while (fgets(buffer, sizeof(buffer), file) != NULL)
			{
				printf("Line read = %s\n", buffer);
				strcpy(strMsg, buffer);
				send(clientSocket, strMsg, strlen(strMsg) + 1, 0);

			}
			
			fclose(file);

			printf("\nFechou o ficheiro\n");
				
		} 
		else if (strcmp(strRec, "menu") == 0) {

			char line[100];
			char StrMenu[1024] = "";
			

			FILE* file = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Menu.txt", "r");
			// Checks if the file was opened successfully
			if (file == NULL)
			{
				fputs("Failed to open the file\n", stderr);
				return -1;
			}

			// fgets here reads an entire line or 99 characters (+1 for \0) at a time, whichever comes first
			while (fgets(line, sizeof(line), file) != NULL)
			{
				strcat(StrMenu, line);
			}
			fclose(file);
			strcpy(strMsg, StrMenu);
			send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
			ZeroMemory(strRec, 1024);
			ZeroMemory(strMsg, 1024);
			

		
			
			// Recber para escolher a opcao do Menu
			recv(clientSocket, strRec, 1024, 0);

			if (strcmp(strRec, "1") == 0) {

				char lineTeatro[100];
				char StrTeatro[1024] = "";

				FILE* fileTeatro = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\teatros.txt", "r");
				// Checks if the file was opened successfully
				if (fileTeatro == NULL)
				{
					fputs("Failed to open the file\n", stderr);
					return -1;
				}

				// fgets here reads an entire line or 99 characters (+1 for \0) at a time, whichever comes first
				while (fgets(lineTeatro, sizeof(lineTeatro), fileTeatro) != NULL)
				{
					strcat(StrTeatro, lineTeatro);

				}
				fclose(fileTeatro);
				strcpy(strMsg, StrTeatro);
				send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
				ZeroMemory(strRec, 1024);
				ZeroMemory(strMsg, 1024);

				// Recber para escolher os horarios dos Teatro
				recv(clientSocket, strRec, 1024, 0);

				if (strcmp(strRec, "1") == 0) {
					
					// abrir e escrever no ficheiro de Logs.
					FILE* fp22;

					fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
					if (fp22 == NULL) {
						printf("ficheiro nao encontrado\n");
						exit(-1);
					}

					time_t now = time(0);
					// convert now to string form
					char* dt = ctime(&now);
					strtok(dt, "\n");

					fprintf(fp22, "%s:  Entrou no Horario Lisboa.\n", dt);
					fclose(fp22);

					//Abir as Horas Exatas defenidas no Horario.txt no ficheiro dos Logs
					int j = 0;
					char H_L[5][100] =
					{ "",
					  "",
					  "",
					  "",
					  ""
					};
					char lineHorarioL[100];
					char StrHorarioL[1024] = "";


					FILE* fileHorarioL = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Horarios_L.txt", "r");
					// Checks if the file was opened successfully
					if (fileHorarioL == NULL)
					{
						fputs("Failed to open the file\n", stderr);
						return -1;
					}

					// fgets here reads an entire line or 99 characters (+1 for \0) at a time, whichever comes first
					while (fgets(lineHorarioL, sizeof(lineHorarioL), fileHorarioL) != NULL)
					{
						strcat(StrHorarioL, lineHorarioL);
						strcat(H_L[j], lineHorarioL);
						strtok(H_L[j], "\n");
						j++;
					}
					fclose(fileHorarioL);
					strcpy(strMsg, StrHorarioL);
					send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
					ZeroMemory(strRec, 1024);
					ZeroMemory(strMsg, 1024);

					// Count
					count++;
					printf("");
					
					// Recber para escolher os horarios dos Teatro
					recv(clientSocket, strRec, 1024, 0);
					if (strcmp(strRec, "1") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Lisboa.\n", dt, H_L[0]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Lisboa\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);
					}
					else if (strcmp(strRec, "2") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Lisboa.\n", dt, H_L[1]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Lisboa\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);
					}
					else if (strcmp(strRec, "3") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Lisboa.\n", dt, H_L[2]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Lisboa\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);

					}
					else if (strcmp(strRec, "4") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Lisboa.\n", dt, H_L[3]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Lisboa\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);

					}
					else if (strcmp(strRec, "5") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Lisboa.\n", dt, H_L[4]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Lisboa\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);

					}
					else{
							
						strcpy(strMsg, "\nNao existem mais opcoes de Horarios em Lisboa!\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
					}

				}
				else if (strcmp(strRec, "2") == 0) {

					
					// abrir e escrever no ficheiro de Logs.
					FILE* fp22;

					fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
					if (fp22 == NULL) {
						printf("ficheiro na encontrado\n");
						exit(-1);
					}
					// Mete o date time nos logs
					time_t now = time(0);
					// convert now to string form
					char* dt = ctime(&now);
					strtok(dt, "\n");

					fprintf(fp22, "%s:  Entrou no Horario Coimbra.\n", dt);
					fclose(fp22);

					int j = 0;
					char H_C[5][100] =
					{ "",
					  "",
					  "",
					  "",
					  ""
					};

					char lineHorarioC[100];
					char StrHorarioC[1024] = "";

					FILE* fileHorarioC = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Horarios_C.txt", "r");
					// Checks if the file was opened successfully
					if (fileHorarioC == NULL)
					{
						fputs("Failed to open the file\n", stderr);
						return -1;
					}

					// fgets here reads an entire line or 99 characters (+1 for \0) at a time, whichever comes first
					while (fgets(lineHorarioC, sizeof(lineHorarioC), fileHorarioC) != NULL)
					{
						strcat(StrHorarioC, lineHorarioC);
						strcat(H_C[j], lineHorarioC);
						strtok(H_C[j], "\n");
						j++;

					}
					fclose(fileHorarioC);
					strcpy(strMsg, StrHorarioC);
					send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
					ZeroMemory(strRec, 1024);
					ZeroMemory(strMsg, 1024);

					// Recber para escolher os horarios dos Teatro
					recv(clientSocket, strRec, 1024, 0);
					if (strcmp(strRec, "1") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Coimbra.\n", dt, H_C[0]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Coimbra\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;
						
						itoa(bilhetes, VisitouL, 10);

					}
					else if (strcmp(strRec, "2") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Coimbra.\n", dt, H_C[1]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Coimbra\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);

					}
					else if (strcmp(strRec, "3") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Coimbra.\n", dt, H_C[2]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Coimbra\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);

					}
					else if (strcmp(strRec, "4") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Coimbra.\n", dt, H_C[3]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Coimbra\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);

					}
					else if (strcmp(strRec, "5") == 0) {
					// abrir e escrever no ficheiro de Logs.
					FILE* fp22;

					fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
					if (fp22 == NULL) {
						printf("ficheiro na encontrado\n");
						exit(-1);
					}
					// Mete o date time nos logs
					time_t now = time(0);
					// convert now to string form
					char* dt = ctime(&now);
					strtok(dt, "\n");

					fprintf(fp22, "%s:  Bilhete [%s] Comprado em Coimbra.\n", dt, H_C[4]);
					fclose(fp22);

					strcpy(strMsg, "\nBilhete Comprado em Coimbra\n");
					send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
					bilhetes++;

					itoa(bilhetes, VisitouL, 10);

					}
					else {
						printf("Nao existem mais opcoes de Horarios em Coimbra!\n");
						strcpy(strMsg, "\nNao existem mais opcoes de Horarios em Coimbra!\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
					}
					
					
				}
				else if (strcmp(strRec, "3") == 0) {

				// abrir e escrever no ficheiro de Logs.
				FILE* fp22;

				fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
				if (fp22 == NULL) {
					printf("ficheiro na encontrado\n");
					exit(-1);
				}
				// Mete o date time nos logs
				time_t now = time(0);
				// convert now to string form
				char* dt = ctime(&now);
				strtok(dt, "\n");

				fprintf(fp22, "%s:  Entrou no Horario Viseu.\n", dt);
				fclose(fp22);

				int j = 0;
				char H_V[5][100] =
				{ "",
				  "",
				  "",
				  "",
				  ""
				};

					char lineHorarioV[100];
					char StrHorarioV[1024] = "";

					FILE* fileHorarioV = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Horarios_V.txt", "r");
					// Checks if the file was opened successfully
					if (fileHorarioV == NULL)
					{
						fputs("Failed to open the file\n", stderr);
						return -1;
					}

					// fgets here reads an entire line or 99 characters (+1 for \0) at a time, whichever comes first
					while (fgets(lineHorarioV, sizeof(lineHorarioV), fileHorarioV) != NULL)
					{
						strcat(StrHorarioV, lineHorarioV);
						strcat(H_V[j], lineHorarioV);
						strtok(H_V[j], "\n");
						j++;
					}
					fclose(fileHorarioV);
					strcpy(strMsg, StrHorarioV);
					send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
					ZeroMemory(strRec, 1024);
					ZeroMemory(strMsg, 1024);

					// Recber para escolher os horarios dos Teatro
					recv(clientSocket, strRec, 1024, 0);
					if (strcmp(strRec, "1") == 0) {

						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Viseu.\n", dt, H_V[0]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Viseu\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);

					}
					else if (strcmp(strRec, "2") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Viseu.\n", dt, H_V[1]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Viseu\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);

					}
					else if (strcmp(strRec, "3") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Viseu.\n", dt, H_V[2]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Viseu\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);

					}
					else if (strcmp(strRec, "4") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Viseu.\n", dt, H_V[3]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Viseu\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);

					}
					else if (strcmp(strRec, "5") == 0) {
					// abrir e escrever no ficheiro de Logs.
					FILE* fp22;

					fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
					if (fp22 == NULL) {
						printf("ficheiro na encontrado\n");
						exit(-1);
					}
					// Mete o date time nos logs
					time_t now = time(0);
					// convert now to string form
					char* dt = ctime(&now);
					strtok(dt, "\n");

					fprintf(fp22, "%s:  Bilhete [%s] Comprado em Viseu.\n", dt, H_V[4]);
					fclose(fp22);

					strcpy(strMsg, "\nBilhete Comprado em Viseu\n");
					send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
					bilhetes++;

					itoa(bilhetes, VisitouL, 10);

					}
					else {
						printf("Nao existem mais opcoes de Horarios em Viseu!\n");
						strcpy(strMsg, "\nNao existem mais opcoes de Horarios em Viseu!\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
					}

				}
				else if (strcmp(strRec, "4") == 0) {
				// abrir e escrever no ficheiro de Logs.
				FILE* fp22;

				fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
				if (fp22 == NULL) {
					printf("ficheiro na encontrado\n");
					exit(-1);
				}
				// Mete o date time nos logs
				time_t now = time(0);
				// convert now to string form
				char* dt = ctime(&now);
				strtok(dt, "\n");

				fprintf(fp22, "%s:  Entrou no Horario Vila Real.\n", dt);
				fclose(fp22);

				int j = 0;
				char H_VR[5][100] =
				{ "",
				  "",
				  "",
				  "",
				  ""
				};

					char lineHorarioVR[100];
					char StrHorarioVR[1024] = "";

					FILE* fileHorarioVR = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Horarios_VR.txt", "r");
					// Checks if the file was opened successfully
					if (fileHorarioVR == NULL)
					{
						fputs("Failed to open the file\n", stderr);
						return -1;
					}

					// fgets here reads an entire line or 99 characters (+1 for \0) at a time, whichever comes first
					while (fgets(lineHorarioVR, sizeof(lineHorarioVR), fileHorarioVR) != NULL)
					{
						strcat(StrHorarioVR, lineHorarioVR);
						strcat(H_VR[j], lineHorarioVR);
						strtok(H_VR[j], "\n");
						j++;
					}
					fclose(fileHorarioVR);
					strcpy(strMsg, StrHorarioVR);
					send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
					ZeroMemory(strRec, 1024);
					ZeroMemory(strMsg, 1024);

					// Recber para escolher os horarios dos Teatro
					recv(clientSocket, strRec, 1024, 0);
					if (strcmp(strRec, "1") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Vila Real.\n", dt, H_VR[0]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Vila Real\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);
					}
					else if (strcmp(strRec, "2") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Vila Real.\n", dt, H_VR[1]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Vila Real\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);

					}
					else if (strcmp(strRec, "3") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Vila Real.\n", dt, H_VR[2]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Vila Real\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);
					}
					else if (strcmp(strRec, "4") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Vila Real.\n", dt, H_VR[3]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Vila Real\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

						itoa(bilhetes, VisitouL, 10);
					}
					else if (strcmp(strRec, "4") == 0) {
						// abrir e escrever no ficheiro de Logs.
						FILE* fp22;

						fp22 = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "a");
						if (fp22 == NULL) {
							printf("ficheiro na encontrado\n");
							exit(-1);
						}
						// Mete o date time nos logs
						time_t now = time(0);
						// convert now to string form
						char* dt = ctime(&now);
						strtok(dt, "\n");

						fprintf(fp22, "%s:  Bilhete [%s] Comprado em Vila Real.\n", dt, H_VR[4]);
						fclose(fp22);

						strcpy(strMsg, "\nBilhete Comprado em Vila Real\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
						bilhetes++;

					}
					else{
						printf("Nao existem mais opcoes de Horarios em Vila real!\n");
						strcpy(strMsg, "\nNao existem mais opcoes de Horarios em Vila real!\n");
						send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
					}
				}
				else {
					printf("Nao existem mais opcoes de Teatro!\n");
					strcpy(strMsg, "\nNao existem mais opcoes de Teatro!\n");
					send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
				}

			}
			else if (strcmp(strRec, "2") == 0) {
				// abrir ficheiro dos logs!
				
				char lineLogs[500];
				char StrLogs[50000] = "";

				FILE* fileLogs = fopen("C:\\Users\\Boost\\Desktop\\Sistemas Distribuidos\\Trabalho Teatro\\Cliente\\Logs.txt", "r");
				// Checks if the file was opened successfully
				if (fileLogs == NULL)
				{
					fputs("Failed to open the file\n", stderr);
					return -1;
				}

				// fgets here reads an entire line or 99 characters (+1 for \0) at a time, whichever comes first
				while (fgets(lineLogs, sizeof(lineLogs), fileLogs) != NULL)
				{
					strcat(StrLogs, lineLogs);

				}
				fclose(fileLogs);
				strcpy(strMsg, StrLogs);
				send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
				ZeroMemory(strRec, 1024);
				ZeroMemory(strMsg, 1024);
				
				

			}
			else if (strcmp(strRec, "3") == 0) {
				printf("\n Comprou %d Bilhetes.\n", bilhetes);
				strcpy(strMsg, VisitouL);
				send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
			}
			else {
				printf("\nErro\n");
				strcpy(strMsg, "\nNao escolheu opcao do Menu!\n");
				send(clientSocket, strMsg, strlen(strMsg) + 1, 0);
			}
			
		
		}
		else if (strcmp(strRec, "ola") == 0) {

			strcpy(strMsg, "\nOla cliente1\n");
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