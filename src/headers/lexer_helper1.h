#ifndef LEXER_HELPER1_H
#define LEXER_HELPER1_H

#include "lexer.h"
#include "parse_redir.h"
#include "utilities.h"

void single_quotes(struct Lexer *lexer, int end);
void if_else_more(struct Lexer *lexer, int end);
void pipeparser(struct Lexer *lexer);
void less(struct Lexer *lexer);
void great(struct Lexer *lexer);
void semi(struct Lexer *lexer);
void and (struct Lexer * lexer);

#endif
