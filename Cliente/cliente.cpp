#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include "Modulos/menus.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

using namespace std;

// g++ cliente.cpp Modulos/menus.cpp -o Cliente.exe -lws2_32

int main(int argc, char *argv[]) {
	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

    cout << endl << "Initialising Winsock..." << endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Failed. Error Code : " << WSAGetLastError() << endl;
		return -1;
	}

    cout << "Initialised." << endl;

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout << "Could not create socket : " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}

    cout << "Socket created." << endl;

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
        cout << "Connection error : " << WSAGetLastError() << endl;
		closesocket(s);
		WSACleanup();
		return -1;
	}

    cout << "Connection stablished with: " << inet_ntoa(server.sin_addr) << "(" << ntohs(server.sin_port) << ")" << endl;

	// SEND and RECEIVE data
    lanzaAplicacion(s, sendBuff, recvBuff);

	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}
