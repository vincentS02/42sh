#include "headers/free_functions.h"
/* FREE FUNCTIONS */

void free_ast(AstNode *node)
{
    for (size_t i = 0; i < node->num_children; i++)
    {
        free_ast(&node->children[i]);
    }
    free(node->children);
    free(node->value);
}

// free after free
void free_lexer_after_free_in_parse(struct Lexer *lexer)
{
    if (lexer)
    {
        free(lexer->token);
        free(lexer);
    }
}
