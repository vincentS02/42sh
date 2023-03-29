#ifndef PARSE_REDIR_H
#define PARSE_REDIR_H

#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "free_functions.h"
#include "lexer.h"
#include "parse_command.h"
#include "parse_shell_command.h"
#include "parser.h"
#include "print_ast.h"

// check whether token is a redir merci.
int is_redir(struct Lexer *lexer);

AstNode *parse_redirection(struct Lexer *lexer, int begin_pos);

AstNode *rec_parsing_redirection(AstNode *node, struct Lexer *lexer,
                                 int begin_pos);

#endif
