#include "token.h"
#include "parser.h"
#include "lexer.h"
#include "node.h"
#include "list.h"

static void *factor(Parser *parser);
static void *term(Parser *parser);
static void *expr(Parser *parser);
static void *program(Parser *parser);
static void *compound_statement(Parser *parser);
static LIST_ENTRY *statement_list(Parser *parser);
static void *statement(Parser *parser);
static void *assignment_statement(Parser *parser);
static void *variable(Parser *parser);
static void *empty(Parser *parser);

static void *program(Parser *parser)
{
    Lexer *lexer = parser->lexer;
    void *node = compound_statement(parser);
    match(lexer, DOT);
    return node;
}

static void *compound_statement(Parser *parser)
{
    Lexer *lexer = parser->lexer;
    match(lexer, BEGIN);
    CompoundNode_t *node = (CompoundNode_t *) malloc(sizeof(CompoundNode_t));
    node->type = NODE_COMPOUND;
    node->statement_list = statement_list(parser);
    match(lexer, END);
    return node;
}

static LIST_ENTRY *statement_list(Parser *parser)
{
    Lexer *lexer = parser->lexer;
    LIST_ENTRY *HEAD = NULL;

    add_list(&HEAD, statement(parser));

    while (lexer->current_token.type == SEMI) {
        match(lexer, SEMI);
        add_list(&HEAD, statement(parser));
    }

    return HEAD;
}

static void *statement(Parser *parser)
{
    Lexer *lexer = parser->lexer;
    void *node = NULL;

    if (lexer->current_token.type == BEGIN) {
        node = compound_statement(parser);
    } else if (lexer->current_token.type  == ID) {
        node = assignment_statement(parser);
    } else {
        node = empty(parser);
    }

    return node;
}

static void *variable(Parser *parser)
{
    VarNode_t *node = (VarNode_t *) malloc(sizeof(VarNode_t));
    node->type = NODE_VAR;
    node->operand = parser->lexer->current_token;
    match(parser->lexer, ID);
    return node;
}

static void *assignment_statement(Parser *parser)
{
    Lexer *lexer = parser->lexer;

    AssignNode_t *node = (AssignNode_t *) malloc(sizeof(AssignNode_t));
    node->type = NODE_ASSIGN;
    node->var = (VarNode_t *) variable(parser);
    match(lexer, ASSIGN);
    node->expr = expr(parser);

    return node;
}

static void *empty(Parser *parser)
{
    NopNode_t *node = (NopNode_t *) malloc(sizeof(NopNode_t));
    node->type = NODE_NOP;
    return node;
}

static void *factor(Parser *parser)
{
    Lexer *lexer = parser->lexer;
    token_t current_token = lexer->current_token;

    if (current_token.type == PLUS) {
        match(lexer, PLUS);
        UnaryNode_t *node = (UnaryNode_t *) malloc(sizeof(UnaryNode_t));
        node->type = NODE_UNARY_OP;
        node->op = current_token;
        node->expr = factor(parser);
        return node;
    } else if (current_token.type == MINUS) {
        match(lexer, MINUS);
        UnaryNode_t *node = (UnaryNode_t *) malloc(sizeof(UnaryNode_t));
        node->type = NODE_UNARY_OP;
        node->op = current_token;
        node->expr = factor(parser);
        return node;
    } else if (current_token.type == INTEGER) {
        match(lexer, INTEGER);
        NumNode_t *node = (NumNode_t *) malloc(sizeof(NumNode_t));
        node->type = NODE_NUM;
        node->operand = current_token;
        return node;
    } else if (current_token.type == LPAREN) {
        match(lexer, LPAREN);
        void *node = expr(parser);
        match(lexer, RPAREN);
        return node;
    } else if (current_token.type == ID) {
        void *node = variable(parser);
        return node;
    }
    
    printf("Unavailable expression!\n");
    exit(0);
}

static void *term(Parser *parser)
{
    void *node = factor(parser);
    Lexer *lexer = parser->lexer;

    while (lexer->current_token.type == MULTIPLY || \
           lexer->current_token.type == DIVIDE   || \
           lexer->current_token.type == POWER) {
        
        token_t current_token = lexer->current_token;
        
        if (current_token.type == MULTIPLY) {
            match(lexer, MULTIPLY);
        }

        if (current_token.type == DIVIDE) {
            match(lexer, DIVIDE);
        }

        if (current_token.type == POWER) {
            match(lexer, POWER);
        }
        
        BinNode_t *space = (BinNode_t *) malloc(sizeof(BinNode_t));
        space->type = NODE_BINARY_OP;
        space->op = current_token;
        space->left = node;
        space->right = factor(parser);

        node = space;
    }
    return node;
}

static void *expr(Parser *parser)
{
    Lexer *lexer = parser->lexer;
    void *node = term(parser);

    while (lexer->current_token.type != NONE && \
           lexer->current_token.type != RPAREN && \
           lexer->current_token.type != SEMI && \
           lexer->current_token.type != END) {
        
        token_t current_token = lexer->current_token;
        
        switch(current_token.type) {
            case PLUS:
                match(lexer, PLUS);
                break;
            case MINUS:
                match(lexer, MINUS);
                break;
            default:
                break;
        }

        BinNode_t *space = (BinNode_t *) malloc(sizeof(BinNode_t));
        space->type = NODE_BINARY_OP;
        space->op = current_token;
        space->left = node;
        space->right = term(parser);

        node = space;
    }
    return node;
}

Parser *parser_init(const char *text)
{
    Parser *parser = (Parser *) malloc(sizeof(Parser));
    if (!parser) {
        printf("parser.c: Not available space to allocate\n");
        exit(0);
    }

    parser->lexer = lexer_init(text);

    return parser;
}

void parser_destroy(Parser *parser)
{
   if (parser->ast) free_node(parser->ast);
   free(parser);
}

void parse(Parser *parser)
{
    parser->ast = program(parser);
}
