#include "menus.h"
#include <iostream>
#include <string.h>
#include <winsock2.h>

#define MAX_OPT 4
#define MAX_USER 32
#define MAX_PASS 128

using namespace std;

void lanzaAplicacion(SOCKET s, char *sendBuff, char *recvBuff){
    bool controlTotal = true;
    char c, cm;
    while(controlTotal){
        c = printInicio();
        switch(c){
            case '1':{
                system("cls");
                if(!printLogin(s, sendBuff, recvBuff)){
                    system("cls");
                    cout << "Usuario incorrecto / no existe. Por favor, intentelo de nuevo." << endl;
                    break;
                }else{
                    controlTotal = false;
                }
                system("cls");
                bool controlMenu = true;
                while(controlMenu){
                    cm = printMenu();
                    switch(cm){
                        case '1':{
                            // Implementar chats
                            break;
                        }
                        case '2':{
                            // Implementar grupos
                            break;
                        }
                        case '3':{
                            // Implementar estados
                            break;
                        }
                        case '4':{
                            // Implementar amigos
                            break;
                        }
                        case 'q':{
                            controlMenu = false;
                            break;
                        }
                        default:{
                            break;
                        }
                    }
                }
            }
            case '2':{
                system("cls");
                // Implementar registro
                break;
            }
            case 'q':{
                system("cls");
                controlTotal = false;
                break;
            }
            default:{
                system("cls");
                break;
            }
        }
    }
}

char printInicio(){
    cout << "------------------------" << endl;
    cout << "|   DEUSTO MESSENGER   |" << endl;
    cout << "------------------------" << endl << endl;

    cout << "1) Iniciar sesion" << endl;
    cout << "2) Registrarse" << endl;
    cout << "q) Salir" << endl;
    cout << "Selecciona una opcion: ";
    char opt[MAX_OPT];
    fgets(opt, MAX_OPT, stdin);
    return *opt;
}

bool printLogin(SOCKET s, char *sendBuff, char *recvBuff){
    cout << "-------------" << endl;
    cout << "|   LOGIN   |" << endl;
    cout << "-------------" << endl << endl;

    cout << "Nombre de usuario: ";
    char user[MAX_USER];
    cin.getline(user, MAX_USER);

    // Comprobar si usuario existe (CODIGO 00)
    char code[512] = "00}";
    strcat(code, user);
    strcat(code, "}");
    strcpy(sendBuff, code);
    send(s, sendBuff, 512, 0);

    recv(s, recvBuff, 512, 0);
    if(strcmp(recvBuff, "No existe") == 0){
        return false;
    }

    // Comprobar si usuario coincide con contrasena (CODIGO 01)
    cout << "Contrasena: ";
    char pass[MAX_PASS];
    cin.getline(pass, MAX_PASS);

    strcpy(code, "01}");
    strcat(code, user);
    strcat(code, "}");
    strcat(code, pass);
    strcat(code, "}");
    
    memset(sendBuff, 0, 512);
    strcpy(sendBuff, code);
    send(s, sendBuff, 512, 0);

    recv(s, recvBuff, 512, 0);
    
    if(strcmp(recvBuff, "No coincide") == 0){
        return false;
    }

    return true;
}

char printMenu(){
    cout << "------------" << endl;
    cout << "|   MENU   |" << endl;
    cout << "------------" << endl << endl;

    cout << "1) Chats" << endl;
    cout << "2) Grupos" << endl;
    cout << "3) Estados" << endl;
    cout << "4) Amigos" << endl;
    cout << "q) Salir" << endl;
    cout << "Seleccione una opcion: ";
    char opt[MAX_OPT];
    fgets(opt, MAX_OPT, stdin);
    return *opt;
}