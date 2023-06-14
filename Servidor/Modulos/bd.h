#ifndef BD_H_
#define BD_H_

#include <stdbool.h>

bool existeUsuario(char *nombre);

char *encrypt(char *pass);

bool comprobarUsuario(char *nombre, char *pass);

#endif /*BD_H_*/