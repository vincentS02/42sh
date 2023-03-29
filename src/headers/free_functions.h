#ifndef FREE_FUNCTIONS_H
#define FREE_FUNCTIONS_H

#define _POSIX_C_SOURCE 200809L
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "lexer.h"
#include "parser.h"

/* FREE FUNCTIONS */

// FREE AST COMPONENTS EXECPT ROOT
void free_ast(AstNode *node);

// FREE LEXER
void free_lexer_after_free_in_parse(struct Lexer *lexer);

#endif
