#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct symtab {
    char name[100];
};

struct symtab symbolTable[100];
int symTableCount = 0;

int findSymbol(char name[]) {
    for (int i = 0; i < symTableCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return 1;
        }
    }
    return -1;
}

int isKeyword(char buffer[]) {
    if (buffer[0] == 'i') {
        if (buffer[1] == 'n' && buffer[2] == 't' && buffer[3] == '\0') {
            return 1;
        } else if (buffer[1] == 'f' && buffer[2] == '\0') {
            return 1;
        }
    } else if (buffer[0] == 'v' && strcmp(buffer, "void") == 0) {
        return 1;
    } else if (buffer[0] == 'm' && strcmp(buffer, "main") == 0) {
        return 1;
    } else if (buffer[0] == 'p' && strcmp(buffer, "printf") == 0) {
        return 1;
    }
    return 0;
}

void check(char buffer[]) {
    int start = 0, final = 0;
    int state = 0;

    while (1) {
        char character = buffer[final];
        if (character == EOF) {
            break;
        }
        switch (state) {
            case 0:
                if (character == '\0') {
                    return;
                } else if (strchr(":()_{},", character) || isspace(character)) {
                    if (!isspace(character)) {
                        printf("\nSpecial Character : %c", character);
                    }
                    start = final;
                    final++;
                } else if (strchr("+-/%*", character)) {
                    printf("\nOperator : %c", character);
                    start = final;
                    final++;
                } else if (isalpha(character)) {
                    start = final;
                    final++;
                    state = 1; // Might be keyword or identifier
                } else if (isdigit(character)) {
                    start = final;
                    final++;
                    state = 2; // value
                } else {
                    final++;
                }
                break;
            case 1:
                if (isalnum(character) || character == '_') {
                    final++;
                } else {
                    char string[100];
                    strncpy(string, buffer + start, final - start);
                    string[final - start] = '\0';

                    if (isKeyword(string)) {
                        printf("\nKeyword : %s", string);
                    } else {
                        printf("\nIdentifier: %s", string);
                        int flag = 0;
                        for (int i = 0; i < symTableCount; i++) {
                            if (strcmp(string, symbolTable[i].name) == 0) {
                                flag = 1;
                                break;
                            }
                        }
                        if (flag == 0) {
                            strcpy(symbolTable[symTableCount].name, string);
                            symTableCount++;
                        }
                    }
                    start = final;
                    final++;
                    state = 0;
                }
                break;
            case 2:
                if (isdigit(character)) {
                    final++;
                } else {
                    char string[100];
                    strncpy(string, buffer + start, final - start);
                    string[final - start] = '\0';
                    printf("\nValue : %s", string);
                    state = 0;
                    start = final;
                    final++;
                }
                break;
        }
    }
}

int main() {
    FILE *fp;
    char buffer[500];
    fp = fopen("input.txt", "r");

    int length = 0;
    char c = fgetc(fp);
    // saving file to a character array
    buffer[0] = c;
    while (c != EOF) {
        buffer[length++] = c;
        c = fgetc(fp);
    }
    buffer[length] = '\0';

    check(buffer);
    printf("\nSYMBOL TABLE\n");
    for (int i = 0; i < symTableCount; i++) {
        printf("\n %d - %s ", i, symbolTable[i].name);
    }

    fclose(fp);
    return 0;
}