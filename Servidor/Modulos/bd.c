#include "bd.h"
#include "sqlite3.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define KEY "ghijklmnopqrstuvwxyzabcdef"

bool existeUsuario(char* nombre) {
    sqlite3 *db;
    sqlite3_stmt *st;
    int res;

    sqlite3_open("proyecto.db", &db);
    char* sent = "select count(*) from usuario where nombre = ?;";

    if(sqlite3_prepare_v2(db, sent, strlen(sent) + 1, &st, NULL) != SQLITE_OK) {
        printf("Error comprobando usuario\n");
        sqlite3_close(db);
    }

    sqlite3_bind_text(st, 1, nombre, strlen(nombre), SQLITE_STATIC);

    res = sqlite3_step(st);

    int cuenta = 0;

    if(res == SQLITE_ROW) {
        cuenta = (int) sqlite3_column_int(st, 0);
    }

    sqlite3_finalize(st);
    sqlite3_close(db);

    if (cuenta == 1) {
        return true;   
    } else {
        return false;
    }
}

char *encrypt(char *pass){
    int len = strlen(pass);
    char *ret = (char*)malloc(sizeof(char)*(len+1));
    int i, j;
    for(int i = 0; i < len; i++){
        if (pass[i] >= 'a' && pass[i] <= 'z') {
            j = pass[i] - 'a';
            ret[i] = KEY[j];
        } else {
            ret[i] = pass[i];
        }
    }
    ret[len] = '\0';
    return ret;
}

bool comprobarUsuario(char *nombre, char *pass){
    sqlite3 *db;
    sqlite3_stmt *st;
    int res;

    sqlite3_open("proyecto.db", &db);
    char* sent = "select count(*) from usuario where nombre = ? and contrasena = ?;";

    if(sqlite3_prepare_v2(db, sent, strlen(sent) + 1, &st, NULL) != SQLITE_OK) {
        printf("Error comprobando usuario\n");
        sqlite3_close(db);
    }

    sqlite3_bind_text(st, 1, nombre, strlen(nombre), SQLITE_STATIC);
    sqlite3_bind_text(st, 2, pass, strlen(pass), SQLITE_STATIC);

    res = sqlite3_step(st);

    int cont;

    if(res == SQLITE_ROW) {
        cont = (int) sqlite3_column_int(st, 0);
    }

    sqlite3_finalize(st);
    sqlite3_close(db);

    if (cont == 1) {
        return true;   
    } else {
        return false;
    }
}