#ifndef PARSER_SHELL_COMMAND_H
#define PARSER_SHELL_COMMAND_H

#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "free_functions.h"
#include "lexer.h"
#include "parse_command.h"
#include "parse_pipeline.h"
#include "parser.h"
#include "print_ast.h"
#include "utilities.h"

int skip_newline(struct Lexer *lexer, int begin_pos);
void one_line_free(AstNode *ast);
void lexer_next_free(struct Lexer *lexer);
int is_good(enum TokenType next, struct Lexer *lexer);
int while_end(struct Lexer *lexer, int first);
int parse_elif(struct Lexer *lexer, AstNode *if_command, int begin_pos,
               AstNode *then);
AstNode *parse_compound_list(struct Lexer *lexer, int begin_pos,
                             enum TokenType next);
AstNode *parse_if(struct Lexer *lexer, int begin_pos);
AstNode *parse_loop(struct Lexer *lexer, int begin_pos, enum TokenType ttype);

#endif
