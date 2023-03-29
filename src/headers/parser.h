#ifndef PARSER_H
#define PARSER_H

#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "utilities.h"

enum ast_type
{
    AST_LIST, // 0
    AST_IF, // 1
    AST_COMMAND, // 2
    AST_ELEMENT, // 3
    AST_PIPELINE, // 4
    AST_REDIR, // 5
    AST_WHILE, // 6
    AST_UNTIL, // 7
};

typedef struct AstNode
{
    enum ast_type type;
    char *value;
    struct AstNode *children;
    size_t num_children;
} AstNode;

AstNode *parse_list_command(struct Lexer *lexer);
void add_child(AstNode *papa, AstNode *son);
AstNode *init_ast(enum ast_type type, struct Lexer *lexer);
void cleanup(struct AstNode *node, struct Lexer *lexer);
AstNode *init_root(enum ast_type type);
AstNode *new_ast(enum ast_type type);
void root_cleanup(struct AstNode *node);

#endif
