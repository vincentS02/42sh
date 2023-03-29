#include "../headers/lexer_helper1.h"

// helper functions 1

void single_quotes(struct Lexer *lexer, int end)
{
    lexer->token->type = TOKEN_SINGLE_QUOTE;
    lexer_next_char(lexer);
    lexer_single_quote(lexer, end);
    lexer_next_char(lexer);
}

void if_else_more(struct Lexer *lexer, int end)
{
    lexer_word(lexer, end);
    if (strcmp(lexer->token->value, "if") == 0)
    {
        lexer->token->type = TOKEN_IF;
    }
    else if (strcmp(lexer->token->value, "then") == 0)
    {
        lexer->token->type = TOKEN_THEN;
    }
    else if (strcmp(lexer->token->value, "else") == 0)
    {
        lexer->token->type = TOKEN_ELSE;
    }
    else if (strcmp(lexer->token->value, "elif") == 0)
    {
        lexer->token->type = TOKEN_ELIF;
    }
    else if (strcmp(lexer->token->value, "fi") == 0)
    {
        lexer->token->type = TOKEN_FI;
    }
    else if (strcmp(lexer->token->value, "do") == 0)
    {
        lexer->token->type = TOKEN_DO;
    }
    else if (strcmp(lexer->token->value, "done") == 0)
    {
        lexer->token->type = TOKEN_DONE;
    }
    else if (strcmp(lexer->token->value, "case") == 0)
    {
        lexer->token->type = TOKEN_CASE;
    }
    else if (strcmp(lexer->token->value, "esac") == 0)
    {
        lexer->token->type = TOKEN_ESAC;
    }
    else if (strcmp(lexer->token->value, "while") == 0)
    {
        lexer->token->type = TOKEN_WHILE;
    }
    else if (strcmp(lexer->token->value, "until") == 0)
    {
        lexer->token->type = TOKEN_UNTIL;
    }
    else if (strcmp(lexer->token->value, "for") == 0)
    {
        lexer->token->type = TOKEN_FOR;
    }
    else if (strcmp(lexer->token->value, "in") == 0)
    {
        lexer->token->type = TOKEN_IN;
    }
    else
    {
        lexer->token->type = TOKEN_WORD;
    }
}
void pipeparser(struct Lexer *lexer)
{
    char buffer[2];
    char buffer2[3];
    char buffer3[4];
    lexer_next_char(lexer);
    if (lexer->ch == '|')
    {
        lexer_next_char(lexer);
        if (lexer->ch == '|')
        {
            lexer->token->type = TOKEN_TRIPLE_PIPE;
            buffer3[0] = '|';
            buffer3[1] = '|';
            buffer3[2] = '|';
            buffer3[3] = 0;
            lexer->token->value = strdup(buffer3);
            lexer_next_char(lexer);
        }
        else
        {
            lexer->token->type = TOKEN_OR_IF;
            buffer2[0] = '|';
            buffer2[1] = '|';
            buffer2[2] = 0;
            lexer->token->value = strdup(buffer2);
        }
    }
    else
    {
        lexer->token->type = TOKEN_PIPE;
        buffer[0] = '|';
        buffer[1] = 0;
        lexer->token->value = strdup(buffer);
    }
}

void helper_less(struct Lexer *lexer, char buffer3[4])
{
    lexer->token->type = TOKEN_DLESSDASH;
    buffer3[0] = '<';
    buffer3[1] = '<';
    buffer3[2] = '-';
    buffer3[3] = 0;
    lexer->token->value = strdup(buffer3);
    lexer_next_char(lexer);
}
void less(struct Lexer *lexer)
{
    char buffer[2];
    char buffer2[3];
    char buffer3[4];
    lexer_next_char(lexer);
    if (lexer->ch == '<')
    {
        lexer_next_char(lexer);
        if (lexer->ch == '-')
        {
            helper_less(lexer, buffer3);
        }
        else
        {
            lexer->token->type = TOKEN_DLESS;
            buffer2[0] = '<';
            buffer2[1] = '<';
            buffer2[2] = 0;
            lexer->token->value = strdup(buffer2);
        }
    }
    else if (lexer->ch == '&')
    {
        lexer->token->type = TOKEN_LESSAND;
        buffer2[0] = '<';
        buffer2[1] = '&';
        buffer2[2] = 0;
        lexer->token->value = strdup(buffer2);
        lexer_next_char(lexer);
    }
    else if (lexer->ch == '>')
    {
        lexer->token->type = TOKEN_LESSGREAT;
        buffer2[0] = '<';
        buffer2[1] = '>';
        buffer2[2] = 0;
        lexer->token->value = strdup(buffer2);
        lexer_next_char(lexer);
    }
    else
    {
        buffer[0] = '<';
        buffer[1] = '\0';
        lexer->token->value = strdup(buffer);
        lexer->token->type = TOKEN_LESS;
    }
}

void great(struct Lexer *lexer)
{
    char buffer[2];
    char buffer2[3];
    lexer_next_char(lexer);
    if (lexer->ch == '>')
    {
        lexer->token->type = TOKEN_DGREAT;
        buffer2[0] = '>';
        buffer2[1] = '>';
        buffer2[2] = '\0';
        lexer->token->value = strdup(buffer2);
        lexer_next_char(lexer);
    }
    else if (lexer->ch == '&')
    {
        lexer->token->type = TOKEN_GREATAND;
        buffer2[0] = '>';
        buffer2[1] = '&';
        buffer2[2] = '\0';
        lexer->token->value = strdup(buffer2);
        lexer_next_char(lexer);
    }
    else if (lexer->ch == '|')
    {
        lexer->token->type = TOKEN_CLOBBER;
        buffer2[0] = '>';
        buffer2[1] = '|';
        buffer2[2] = '\0';
        lexer->token->value = strdup(buffer2);
        lexer_next_char(lexer);
    }
    else
    {
        buffer[0] = '>';
        buffer[1] = '\0';
        lexer->token->value = strdup(buffer);
        lexer->token->type = TOKEN_GREAT;
    }
}
void semi(struct Lexer *lexer)
{
    char buffer[2];
    char buffer2[3];
    lexer_next_char(lexer);
    if (lexer->ch == ';')
    {
        lexer->token->type = TOKEN_DOUBLE_SEMI;
        buffer2[0] = ';';
        buffer2[1] = ';';
        buffer2[2] = 0;
        lexer->token->value = strdup(buffer2);
    }
    else
    {
        lexer->token->type = TOKEN_SEMI;
        buffer[0] = ';';
        buffer[1] = 0;
        lexer->token->value = strdup(buffer);
    }
}

void and (struct Lexer * lexer)
{
    char buffer[2];
    char buffer2[3];
    lexer_next_char(lexer);
    if (lexer->ch == '&')
    {
        lexer->token->type = TOKEN_AND_IF;
        buffer2[0] = '&';
        buffer2[1] = '&';
        buffer2[2] = 0;
        lexer->token->value = strdup(buffer2);
        lexer_next_char(lexer);
    }
    else
    {
        lexer->token->type = TOKEN_AMP;
        buffer[0] = '&';
        buffer[1] = 0;
        lexer->token->value = strdup(buffer);
    }
}
