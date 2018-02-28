#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    /* Operand */
    INTEGER,
    /* Operator */
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    POWER,
    /* Reserved Words */
    BEGIN,
    END,
    /* Identifier */
    ID,
    /* Special Characters */
    ASSIGN,
    SEMI,
    DOT,
    LPAREN,
    RPAREN,
    NONE
} TYPE;

typedef struct __token token_t;

struct __token {
    TYPE type;
    void *value;
};

#endif
