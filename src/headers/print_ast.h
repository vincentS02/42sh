#ifndef PRINT_AST_H
#define PRINT_AST_H

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

void print_ast(AstNode *node);

#endif
