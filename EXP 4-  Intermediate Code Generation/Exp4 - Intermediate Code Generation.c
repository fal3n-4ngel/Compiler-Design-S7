#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPR_LEN 100
#define MAX_TEMP_VARS 50

char expr[MAX_EXPR_LEN];
char temp_vars[MAX_TEMP_VARS][4];
int temp_var_count = 0;
FILE *output_file;

char *new_temp_var() {
    if (temp_var_count >= MAX_TEMP_VARS) {
        printf("Error: too many variables\n");
        exit(1);
    }
    sprintf(temp_vars[temp_var_count], "T%d", temp_var_count + 1);
    return temp_vars[temp_var_count++];
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

char* generate_code(char* expr) {
    int len = strlen(expr);
    int paren_count = 0;
    int op_pos = -1;
    int min_precedence = 3;

    for (int i = len - 1; i >= 0; i--) {
        if (expr[i] == ')') paren_count++;
        else if (expr[i] == '(') paren_count--;
        else if (paren_count == 0) {
            int prec = precedence(expr[i]);
            if (prec > 0 && prec <= min_precedence) {
                min_precedence = prec;
                op_pos = i;
            }
        }
    }

    if (op_pos == -1) {
        if (expr[0] == '(' && expr[len-1] == ')') {
            expr[len-1] = '\0';
            return generate_code(expr + 1);
        }
        return expr;
    }

    char op = expr[op_pos];
    expr[op_pos] = '\0';
    char* left = generate_code(expr);
    char* right = generate_code(expr + op_pos + 1);
    char* temp = new_temp_var();

    fprintf(output_file, "\n%-15s := %s %c %s", temp, left, op, right);
    fprintf(output_file, "\t\t%-10c%-10s%-10s%-10s", op, left, right, temp);
    fprintf(output_file, "\t\t(%d)\t%c", temp_var_count, op);

    if (left[0] == 'T') {
        fprintf(output_file, "\t(%c)", left[1]);
    } else {
        fprintf(output_file, "\t%s", left);
    }

    if (right[0] == 'T') {
        fprintf(output_file, "\t(%c)", right[1]);
    } else {
        fprintf(output_file, "\t%s", right);
    }

    return temp;
}

int main() {
    printf("Enter expression:\n");
    if (fgets(expr, MAX_EXPR_LEN, stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    expr[strcspn(expr, "\n")] = 0;  // Remove newline if present

    output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Error opening output file\n");
        return 1;
    }

    fprintf(output_file, "%-15s\t\t%-30s\t\t%-s\n", "Three Address Code", "Quadruple", "Triple");
    fprintf(output_file, "-------------------------------------------------------------------------------\n");

    char* assignment = strchr(expr, '=');
    if (assignment) {
        *assignment = '\0';
        char* lhs = expr;
        char* rhs = assignment + 1;
        char* result = generate_code(rhs);
        fprintf(output_file, "\n%-15s := %s", lhs, result);
    } else {
        generate_code(expr);
    }

    fclose(output_file);
    printf("Output written to output.txt\n");
    return 0;
}

// Enter expression:
// a=(a+b)
// Output written to output.txt

// Three Address Code		Quadruple                     		Triple
// -------------------------------------------------------------------------------

// T1              := a + b		+         a         b         T1        		(1)	+	a	b
// a               := T1