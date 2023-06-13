#include <stdio.h>
#include <winsock2.h>
#include "Modulos/bd.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
#define MAX_USER 32
#define MAX_PASS 128

// gcc servidor.c Modulos/bd.c Modulos/sqlite3.c -o Servidor.exe -lws2_32

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	//SEND and RECEIVE data
	printf("Waiting for incoming messages from client... \n");
	do {
		int bytes = recv(comm_socket, recvBuff, 512, 0);
		if (bytes > 0) {
			char cod[3];
			strncpy(cod, recvBuff, 2);
			cod[2] = '\0';
			if(strcmp(cod, "00") == 0){
				char *token;
				token = strtok(recvBuff, "}");
				token = strtok(NULL, "}");
				char user[MAX_USER];
				strcpy(user, token);
				memset(sendBuff, 0, 512);
				if(existeUsuario(user)){
					strcpy(sendBuff, "Existe");
					send(comm_socket, sendBuff, 512, 0);
				}else{
					strcpy(sendBuff, "No existe");
					send(comm_socket, sendBuff, 512, 0);
				}
			}else if(strcmp(cod, "01") == 0){
				char *token;
				token = strtok(recvBuff, "}");
				token = strtok(NULL, "}");
				char user[MAX_USER];
				strcpy(user, token);
				token = strtok(recvBuff, "}");
				token = strtok(NULL, "}");
				char pass[MAX_PASS];
				strcpy(pass, token);

				// Comprobar si el usuario existe en la BD
			}
		}
	} while (1);

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}