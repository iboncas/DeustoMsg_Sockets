#ifndef MENUS_H_
#define MENUS_H_

#include <winsock2.h>

void lanzaAplicacion(SOCKET s, char *sendBuff, char *recvBuff);

char printInicio();

bool printLogin(SOCKET s, char *sendBuff, char *recvBuff);

#endif /*MENUS_H_*/