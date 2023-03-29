#ifndef LEXER_HELPER2_H
#define LEXER_HELPER2_H

#include "lexer.h"
#include "lexer_helper1.h"
#include "parse_redir.h"
#include "utilities.h"

void newline(struct Lexer *lexer);
void bang(struct Lexer *lexer);
void lparen(struct Lexer *lexer);
void rparen(struct Lexer *lexer);
void lbrace(struct Lexer *lexer);
void rbrace(struct Lexer *lexer);
void option0(struct Lexer *lexer, int end);
void option1(struct Lexer *lexer, int end);

#endif
