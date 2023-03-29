#ifndef LEXER_H
#define LEXER_H

#define _POSIX_C_SOURCE 200809L
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum TokenType
{
    TOKEN_EOF,
    TOKEN_WORD,
    TOKEN_ASSIGNMENT_WORD,
    TOKEN_IONUMBER,
    TOKEN_AND_IF,
    TOKEN_OR_IF,
    TOKEN_DSEMI,
    TOKEN_LESS,
    TOKEN_GREAT,
    TOKEN_LESSAND,
    TOKEN_GREATAND,
    TOKEN_LESSGREAT,
    TOKEN_DLESSDASH,
    TOKEN_CLOBBER,
    TOKEN_PIPE,
    TOKEN_BANG,
    TOKEN_IF,
    TOKEN_THEN,
    TOKEN_ELSE,
    TOKEN_ELIF,
    TOKEN_FI,
    TOKEN_SEMI,
    TOKEN_AMP,
    TOKEN_NEWLINE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_DGREAT,
    TOKEN_DLESS,
    TOKEN_DO,
    TOKEN_DONE,
    TOKEN_CASE,
    TOKEN_ESAC,
    TOKEN_WHILE,
    TOKEN_UNTIL,
    TOKEN_FOR,
    TOKEN_IN,
    TOKEN_QUOTE,
    TOKEN_DOUBLE_SEMI,
    TOKEN_OTHER,
    TOKEN_BEGIN,
    TOKEN_COMMAND,
    TOKEN_SINGLE_QUOTE,
    TOKEN_TRIPLE_PIPE,
    TOKEN_ERR1
};

struct Token
{
    enum TokenType type;
    char *value;
    // int arse_shell_commandtype;
    struct Token *next;
};

struct Lexer
{
    char *input;
    int pos;
    int len;
    char ch;
    struct Token *token;
    int option;
};

struct Lexer *lexer_init(char *input);
void lexer_next_char(struct Lexer *lexer);
void lexer_next_token(struct Lexer *lexer, int end);
void free_token(struct Token *token);
int isspace2(char c);
void lexer_skip_whitespace(struct Lexer *lexer);
void lexer_word(struct Lexer *lexer, int end);
void lexer_word2(struct Lexer *lexer, int end);
void lexer_single_quote(struct Lexer *lexer, int end);

#endif
