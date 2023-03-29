#include "../headers/print_ast.h"

void rec_ast(AstNode *node, int indent)
{
    for (int i = 0; i < indent; i++)
    {
        printf(" %d ", i);
    }
    printf("%s: %d\n", node->value, node->type);
    for (size_t y = 0; y < node->num_children; y++)
    {
        rec_ast(&node->children[y], indent + 1);
    }
}

void print_ast(AstNode *node)
{
    if (!node)
        printf("oh no node is empty wtf??\n");
    else
    {
        printf("AST: %ld\n", node->num_children);
        for (size_t i = 0; i < node->num_children; i++)
        {
            rec_ast(&node->children[i], 1);
        }
    }
}
