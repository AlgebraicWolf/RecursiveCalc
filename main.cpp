#include <cstdio>
#include <cstdlib>
#include <cassert>

#define expassert(cond) \
    if (!(cond)) {\
            if(errpos != nullptr) errpos = expression; \
            return 0; \
        } \

#define validate \
    if(errpos != nullptr) return 0

const char *expression = nullptr;
const char *errpos = nullptr;

int getG(const char *exp);

int getE();

int getP();

int getT();

int getN();

int main() {
    FILE *expFile = fopen("input.txt", "r");

    fseek(expFile, 0, SEEK_END);
    int size = ftell(expFile);
    rewind(expFile);

    char *exp = (char *) calloc(size + 1, sizeof(char));
    fread(exp, sizeof(char), size, expFile);
    fclose(expFile);

    int result = getG(exp);
    if(errpos != nullptr) {
        printf("An error was found at position %d\n", errpos - exp + 1);
    }
    else {
        printf("Calculation result: %d\n", result);
    }
    return 0;
}

int getG(const char *exp) {
    validate;

    expression = exp;

    int val = getE();

    expassert(*expression == '\0');

    return val;
}

int getE() {
    int val = getT();
    validate;

    while(*expression == '+' || *expression == '-') {
        char op = *expression;

        expression++;
        int val2 = getT();
        validate;
        if(op == '+')
            val += val2;
        else
            val -= val2;
    }
    return val;
}

int getT() {
    int val = getP();
    validate;

    while(*expression == '*' || *expression == '/') {
        char op = *expression;

        expression++;
        int val2 = getP();
        validate;
        if(op == '*')
            val *= val2;
        else
            val /= val2;
    }
    return val;
}

int getP() {
    int val = 0;
    if(*expression == '(') {
        expression++;
        val = getE();
        validate;
        expassert(*expression == ')');
        expression++;
    }
    else {
        val = getN();
        validate;
    }
    return val;
}

int getN() {
    validate;

    expassert(*expression <= '9' && *expression >= '0');

    int val = 0;

    while(*expression <= '9' && *expression >= '0') {
        val = val * 10 + *expression - '0';
        expression++;
    }

    return val;
}