#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "lexer.h"

static void add_reserved_word(Reserved_word_table *table, \
                              token_t token)
{
    table->words[table->num] = token;
    table->num += 1;
}

static void init_reserved_word(Reserved_word_table *table)
{
    table->num = 0;

    token_t token = { .type = NONE, .value = NULL};

    /* Add Reserved Words here */
    token.type = BEGIN; token.value = "BEGIN";
    add_reserved_word(table, token);

    token.type = END; token.value = "END";
    add_reserved_word(table, token);

    token.type = INTEGER_DIVIDE; token.value = "div";
    add_reserved_word(table, token);
}

static token_t find_reserved_word(Reserved_word_table *table, \
                                  char *text)
{
    for (int i = 0; i < table->num; i++) {
        char *cmp_reserved_word = (char *) table->words[i].value;
        if (strcmp(cmp_reserved_word, text) == 0) {
            return table->words[i];
        }
    }

    /* It's a identifier */
    /* TODO: strdup(text) needs to be freed */
    token_t token = { .type = ID, .value = strdup(text)};
    return token;
}

static int isDigit(char target)
{
    if (target >= '0' && target <= '9')
        return 1;
    return 0;
}

static int isAlpha(char target)
{
    if ((target >= 'A' && target <= 'Z') ||
        (target >= 'a' && target <= 'z'))
        return 1;
    return 0;
}

static int isLegalCharacter(char target)
{
   if (isDigit(target) || isAlpha(target) || \
       target == '_')
       return 1;
   return 0;
}

static void advance(Lexer *lexer)
{
    lexer->pos += 1;
    if (lexer->pos >= lexer->len) {
        lexer->current_char = EOF;
    } else {
        lexer->current_char = lexer->text[lexer->pos];
    }
}

static char peek(Lexer *lexer)
{
    int peek_pos = lexer->pos + 1;
    if (peek_pos >= lexer->len)
        return EOF;
    return lexer->text[peek_pos];
}

token_t scalar(Lexer *lexer)
{
    char number[_AVAILABLE_DIGITS];
    int i = 0;
    token_t ret;

    /* 4 bytes used to store a integer or floating-point */
    ret.value = malloc(4);

    do {
        number[i++] = lexer->current_char;
        advance(lexer);
    } while (lexer->current_char != EOF && isDigit(lexer->current_char));

    if (lexer->current_char == '.') {
        number[i++] = lexer->current_char;
        advance(lexer);

        while (lexer->current_char != EOF && \
               isDigit(lexer->current_char)) {
            number[i++] = lexer->current_char;
            advance(lexer);
        }

        * (float *) ret.value = (float) atof(number);
        ret.type = REAL_CONST;
    } else {
        * (int *) ret.value = atoi(number);
        ret.type = INTEGER_CONST;
    }

    return ret;
}

token_t integer(Lexer *lexer)
{
    char number[_AVAILABLE_DIGITS];
    int i = 0;

    do {
        number[i++] = lexer->current_char;
        advance(lexer);
    } while (lexer->current_char != EOF && isDigit(lexer->current_char));
    number[i] = '\0';
    
    token_t ret = {.type = NONE, .value = NULL};
    ret.value = malloc(sizeof(int));
    * (int *) ret.value = atoi(number);
    ret.type = INTEGER_CONST;
    return ret;
}

token_t id(Lexer *lexer)
{
    char text[_AVAILABLE_DIGITS];
    int i = 0;

    do {
        text[i++] = lexer->current_char;
        advance(lexer);
    } while (lexer->current_char != EOF && isLegalCharacter(lexer->current_char));
    text[i] = '\0';

    return find_reserved_word(&lexer->RESERVED_WORDS, text);
}

void skip_whitespace_newline(Lexer *lexer)
{
    do {
        advance(lexer);
    } while (lexer->current_char == ' ' || lexer->current_char == '\n');
}

token_t get_next_token(Lexer *lexer)
{
    token_t ret = {.type = NONE, .value = NULL};

    if (lexer->current_char != EOF) {
        if (lexer->current_char == ' ' || lexer->current_char == '\n')
            skip_whitespace_newline(lexer);

        if (lexer->current_char == EOF)
            return ret;

        if (isDigit(lexer->current_char)) {
            return scalar(lexer);
        }

        if (lexer->current_char == '+') {
            ret.type = PLUS;
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == '-') {
            ret.type = MINUS;
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == '*') {
            ret.type = MULTIPLY;
            advance(lexer);
            return ret;
        }

        /*
        if (lexer->current_char == '/') {
            ret.type = DIVIDE;
            advance(lexer);
            return ret;
        }
        */

        if (lexer->current_char == '(') {
            ret.type = LPAREN;
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == ')') {
            ret.type = RPAREN;
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == '^') {
            ret.type = POWER;
            advance(lexer);
            return ret;
        }

        if (isAlpha(lexer->current_char) || \
            lexer->current_char == '_') {
            return id(lexer);
        }

        if (lexer->current_char == ':' &&
            peek(lexer) == '=') {
            ret.type = ASSIGN;
            advance(lexer);
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == ';') {
            ret.type = SEMI;
            advance(lexer);
            return ret;
        }

        if (lexer->current_char == '.') {
            ret.type = DOT;
            advance(lexer);
            return ret;
        }

        printf("interpreter.c: Unavailable char exists\n");
        exit(0);
    }
    return ret;
}

void match(Lexer *lexer, TYPE type)
{
    if (lexer->current_token.type == type) {
        lexer->current_token = get_next_token(lexer);
    } else {
        printf("interpreter.c: Failed to match rules\n");
        exit(0);
    }
}

Lexer *lexer_init(const char *text)
{
    Lexer *lexer = (Lexer *) malloc(sizeof(Lexer));
    if (!lexer) {
        printf("lexer.c: No available memory for use\n");
        exit(0);
    }
    lexer->pos = 0;
    lexer->len = strlen(text);
    lexer->text = text;
    lexer->current_char = text[0];
    init_reserved_word(&lexer->RESERVED_WORDS);
    lexer->current_token = get_next_token(lexer);
    return lexer;
}

void lexer_destroy(Lexer *lexer)
{
    free(lexer);
}
