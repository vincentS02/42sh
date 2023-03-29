#ifndef PARSE_PIPELINE_H
#define PARSE_PIPELINE_H

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

AstNode *parse_pipeline(struct Lexer *lexer, int end, int begin_pos);
int has_pipe(const char *str, size_t end);

#endif
