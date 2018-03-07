#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    /* Constant */
    INTEGER_CONST,
    REAL_CONST,
    /* Operator */
    PLUS,
    MINUS,
    MULTIPLY,
    INTEGER_DIVIDE,
    REAL_DIVIDE,
    POWER,
    /* Reserved Words */
    PROGRAM,
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
