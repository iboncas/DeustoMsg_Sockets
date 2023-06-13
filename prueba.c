#include <stdio.h>
#include <string.h>

int main() {
    char input[] = "type}jesus}ramirez";
    char *token;

    // Extracting the name
    token = strtok(input, "}");
    token = strtok(NULL, "}");
    char name[50];
    strcpy(name, token);

    // Extracting the password
    token = strtok(NULL, "}");
    char password[50];
    strcpy(password, token);

    // Print the extracted values
    printf("Name: %s\n", name);
    printf("Password: %s\n", password);

    return 0;
}