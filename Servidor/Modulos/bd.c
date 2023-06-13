#include "bd.h"
#include "sqlite3.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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