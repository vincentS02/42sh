#ifndef UTILITIES_H
#define UTILITIES_H

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

void remove_newline(char *string);
int is_delimited_by_single_quotes(const char *str);
void remove_single_quotes(char *str);
int is_command(struct Lexer *lexer, int begin, int end);
int isNumber(char c);
int is_empty_string(const char *str);

#endif
