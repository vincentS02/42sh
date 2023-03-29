#include "../headers/lexer_helper2.h"

// helper functions 2

void newline(struct Lexer *lexer)
{
    char buffer[2];
    buffer[0] = '\n';
    buffer[1] = '\0';
    lexer->token->value = strdup(buffer);
    lexer->token->type = TOKEN_NEWLINE;
    lexer_next_char(lexer);
}

void bang(struct Lexer *lexer)
{
    char buffer[2];
    lexer->token->type = TOKEN_BANG;
    buffer[0] = '!';
    buffer[1] = '\0';
    lexer->token->value = strdup(buffer);
    lexer_next_char(lexer);
}

void lparen(struct Lexer *lexer)
{
    char buffer[2];
    lexer->token->type = TOKEN_LPAREN;
    buffer[0] = '(';
    buffer[1] = '\0';
    lexer->token->value = strdup(buffer);
    lexer_next_char(lexer);
}

void rparen(struct Lexer *lexer)
{
    char buffer[2];
    lexer->token->type = TOKEN_RPAREN;
    buffer[0] = ')';
    buffer[1] = '\0';
    lexer->token->value = strdup(buffer);
    lexer_next_char(lexer);
}

void lbrace(struct Lexer *lexer)
{
    char buffer[2];
    lexer->token->type = TOKEN_LBRACE;
    buffer[0] = '{';
    buffer[1] = '\0';
    lexer->token->value = strdup(buffer);
    lexer_next_char(lexer);
    lexer->token->type = TOKEN_LBRACE;
    buffer[0] = '{';
    buffer[1] = '\0';
    lexer->token->value = strdup(buffer);
    lexer_next_char(lexer);
}

void rbrace(struct Lexer *lexer)
{
    char buffer[2];
    lexer->token->type = TOKEN_RBRACE;
    buffer[0] = '}';
    buffer[1] = '\0';
    lexer->token->value = strdup(buffer);
    lexer_next_char(lexer);
}

void option0(struct Lexer *lexer, int end)
{
    switch (lexer->ch)
    {
    case ';':
        semi(lexer);
        break;
    case '&':
        and(lexer);
        break;
    case '|':
        pipeparser(lexer);
        break;
    case '<':
        less(lexer);
        break;
    case '>':
        great(lexer);
        break;
    case '!':
        bang(lexer);
        break;
    case '\n':
        newline(lexer);
        break;
    case '(':
        lparen(lexer);
        break;
    case ')':
        rparen(lexer);
        break;
    case '{':
        lbrace(lexer);
        break;
    case '}':
        rbrace(lexer);
        break;
    default:
        lexer_word2(lexer, end);
        lexer->token->type = TOKEN_OTHER;
        break;
    }
}
void option1(struct Lexer *lexer, int end)
{
    switch (lexer->ch)
    {
    case '|':
        pipeparser(lexer);
        break;
    case '<':
        less(lexer);
        break;
    case '>':
        great(lexer);
        break;
    case ';':
        semi(lexer);
        break;
    case '&':
        and(lexer);
        break;
    case '\n':
        newline(lexer);
        break;
    default:
        lexer_word2(lexer, end);
        lexer->token->type = TOKEN_OTHER;
        break;
    }
}
