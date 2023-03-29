#ifndef PARSE_COMMAND_H
#define PARSE_COMMAND_H

#include "free_functions.h"
#include "lexer.h"
#include "parse_pipeline.h"
#include "parse_redir.h"
#include "parse_shell_command.h"
#include "parser.h"
#include "print_ast.h"
#include "utilities.h"

// simple command

AstNode *parse_simple_command(struct Lexer *lexer, int end, int begin_pos);
AstNode *new_ast(enum ast_type type);
void add_child(AstNode *papa, AstNode *son);
void init_lexer(struct Lexer *lexer, int begin_pos, int option);

#endif
