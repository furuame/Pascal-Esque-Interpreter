#include "node.h"
#include "token.h"

/* return n ^ k */
int mypow(int n, int k)
{
    int ret = n;
    
    if (k <= 0) return 1;

    for (int i = 0; i < k - 1; i++) {
        ret *= n;
    }
    return ret;
}

int visit_BinNode(BinNode_t *node)
{
    switch (node->op.type) {
        case PLUS:
            return visit(node->left) + visit(node->right);
        case MINUS:
            return visit(node->left) - visit(node->right);
        case MULTIPLY:
            return visit(node->left) * visit(node->right);
        case DIVIDE:
            return visit(node->left) / visit(node->right);
        case POWER:
            return mypow(visit(node->left), visit(node->right));
        default:
            printf("node.c: Unavailable op type\n");
            exit(0);
    }
}

int visit_NumNode(NumNode_t *node)
{
    return * (int *) node->operand.value;
}

int visit_UnaryNode(UnaryNode_t *node)
{
    switch (node->op.type) {
        case PLUS:
            return visit(node->expr);
        case MINUS:
            return -1 * visit(node->expr);
        default:
            printf("node.c: Unavailabe op type\n");
            exit(0);
    }
}

int visit(void *node)
{
    switch (*((AST_NODE_TYPE *) node)) {
        case NODE_NUM:
            return visit_NumNode((NumNode_t *) node);
        case NODE_BINARY_OP:
            return visit_BinNode((BinNode_t *) node);
        case NODE_UNARY_OP:
            return visit_UnaryNode((UnaryNode_t *) node);
        default:
            printf("node.c: error\n");
            exit(0);
    }
}

void free_node(void *node)
{
    if (*((AST_NODE_TYPE *) node) == NODE_BINARY_OP) {
        free_node(((BinNode_t *) node)->left);
        free_node(((BinNode_t *) node)->right);
    }

    if (*((AST_NODE_TYPE *) node) == NODE_UNARY_OP) {
        free_node(((UnaryNode_t *) node)->expr);
    }

    if (*((AST_NODE_TYPE *) node) == NODE_NUM) {
        free(((NumNode_t *) node)->operand.value);
    }

    free(node);
}
