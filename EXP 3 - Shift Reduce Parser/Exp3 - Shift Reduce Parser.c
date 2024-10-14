//Adithya Krishnan
//Shift Reduce Parser

#include <stdio.h>
#include <string.h>

struct productionRules {
    char left[10];
    char right[10];
};

int isReducable(char stack[], int *stackTop, struct productionRules prodRules[], int ruleCount, char expression[], int index) {
    for (int i = 0; i < ruleCount; i++) {
        int lenRight = strlen(prodRules[i].right);
        int lenLeft = strlen(prodRules[i].left);
        if (*stackTop >= lenRight && strcmp(&stack[*stackTop - lenRight], prodRules[i].right) == 0) {
            *stackTop -= lenRight;
            strcpy(&stack[*stackTop], prodRules[i].left);
            *stackTop += lenLeft;
            stack[*stackTop] = '\0';

            printf("\n%s - %s - Reduce %s -> %s", stack, &expression[index], prodRules[i].left, prodRules[i].right);
            return 1;
        }
    }
    return 0;
}

int parse(char expression[], struct productionRules prodRules[], int ruleCount) {
    char stack[40];
    int stackTop = 1;
    stack[0] = '$';
    stack[1] = '\0';
    char startingSymbol[20];
    sprintf(startingSymbol, "$%s", prodRules[0].left);

    for (int i = 0; i < strlen(expression) + 1; i++) {
        stack[stackTop++] = expression[i];
        stack[stackTop] = '\0';
        printf("\n%s - %s - %s", stack, &expression[i+1], "shift");

        while (isReducable(stack, &stackTop, prodRules, ruleCount, expression, i+1));
        if (strcmp(stack, startingSymbol) == 0 && i == strlen(expression) - 1) {
            printf("\nACCEPT");
            return 1;
        }
    }
    return 0;
}

int main() {
    printf("Enter the number of production Rules: ");
    int numberOfProductionRules = 0;
    scanf("%d", &numberOfProductionRules);
    struct productionRules prodRules[numberOfProductionRules];
    printf("\nEnter the Production Rules:\n");
    for (int i = 0; i < numberOfProductionRules; i++) {
        char rule[100];
        printf("\n%d: ", i+1);
        scanf("%s", rule);
        strcpy(prodRules[i].left, strtok(rule, "->"));
        strcpy(prodRules[i].right, strtok(NULL, "->"));
    }
    printf("Enter the expression: ");
    char expression[20];
    scanf("%s", expression);
    expression[strcspn(expression, "\n")] = '\0';
    parse(expression, prodRules, numberOfProductionRules);
    return 0;
}

//Enter the number of production Rules:3
//
//Enter the Production Rules :
//
//1:S->(S)
//
//2:S->SS
//
//3:S->a
//        Enter the expression:(aaa)
//
//$( - aaa) - shift
//$(a - aa) - shift
//$(S - aa) - Reduce S -> a
//$(Sa - a) - shift
//$(SS - a) - Reduce S -> a
//$(S - a) - Reduce S -> SS
//$(Sa - ) - shift
//$(SS - ) - Reduce S -> a
//$(S - ) - Reduce S -> SS
//$(S) -  - shift
//        $S -  - Reduce S -> (S)
//ACCEPT