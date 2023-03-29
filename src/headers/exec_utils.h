#ifndef EXEC_UTILS_H
#define EXEC_UTILS_H

#define _POSIX_C_SOURCE 200809L
#include <ctype.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* our files */

#include "free_functions.h"
#include "lexer.h"
#include "parse_command.h"
#include "parse_input.h"
#include "parse_pipeline.h"
#include "parse_redir.h"
#include "parse_shell_command.h"
#include "parser.h"
#include "print_ast.h"

/* exec files */

#include "all_builtins.h"
#include "exec_cmd.h"
#include "exec_main.h"
#include "exec_pipeline.h"
#include "exec_redir.h"
#include "exec_shell_cmd.h"

void success(struct AstNode *ast);

#endif
