#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

char input[100];
int i = 0;

// Function prototypes
bool E();
bool EP();
bool T();
bool TP();
bool F();

void main() {
    printf("Recursive descent parsing for the grammar:\n");
    printf("E -> TE'\nE' -> +TE' | ε\nT -> FT'\nT' -> *FT' | ε\nF -> (E) | char\n\n");

    printf("Enter the string to be checked: ");
    scanf("%s", input);

    if (E() && input[i] == '\0') {
        printf("String is accepted\n");
    } else {
        printf("String is not accepted\n");
    }
}

bool E() {
    return T() && EP();
}

bool EP() {
    if (input[i] == '+') {
        i++;
        return T() && EP();
    }
    return true; // ε production
}

bool T() {
    return F() && TP();
}

bool TP() {
    if (input[i] == '*') {
        i++;
        return F() && TP();
    }
    return true; // ε production
}

bool F() {
    if (input[i] == '(') {
        i++;
        if (E() && input[i] == ')') {
            i++;
            return true;
        }
        return false;
    }
    if (isalnum(input[i])) {
        i++;
        return true;
    }
    return false;
}

// Recursive descent parsing for the grammar:
// E -> TE'
// E' -> +TE' | ε
// T -> FT'
// T' -> *FT' | ε
// F -> (E) | char

// Enter the string to be checked: 1+2
// String is accepted