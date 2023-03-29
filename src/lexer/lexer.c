#include "../headers/lexer_all.h"

struct Lexer *lexer_init(char *input)
{
    struct Lexer *lexer = malloc(sizeof(struct Lexer));
    if (lexer == NULL)
    {
        exit(2);
    }
    lexer->input = input;
    lexer->len = strlen(input);
    lexer->pos = 0;
    lexer->option = 0;
    lexer->ch = input[0];
    lexer->token = malloc(sizeof(struct Token));
    lexer->token->type = TOKEN_BEGIN;
    if (lexer->token == NULL)
    {
        exit(2);
    }

    return lexer;
}

int isspace2(char c)
{
    if (c == ' ' || c == '\r' || c == '\t')
    {
        return 1;
    }
    return 0;
}
void lexer_skip_whitespace(struct Lexer *lexer)
{
    while (isspace2(lexer->ch))
    {
        lexer_next_char(lexer);
    }
}

void lexer_skip_comment(struct Lexer *lexer)
{
    while (lexer->ch != '\n' && lexer->ch != 0)
    {
        lexer_next_char(lexer);
    }
}

int lexer_is_digit(char ch)
{
    return ch >= '0' && ch <= '9';
}

void lexer_number(struct Lexer *lexer)
{
    char buffer[13000];
    int i = 0;
    while (lexer_is_digit(lexer->ch))
    {
        buffer[i++] = lexer->ch;
        lexer_next_char(lexer);
    }
    buffer[i] = 0;
    lexer->token->value = strdup(buffer);
}

int lexer_is_alpha(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

void lexer_next_char(struct Lexer *lexer)
{
    lexer->pos++;
    if (lexer->pos >= lexer->len)
    {
        lexer->ch = 0;
    }
    else
    {
        lexer->ch = lexer->input[lexer->pos];
    }
}

void lexer_word(struct Lexer *lexer, int end)
{
    char buffer[13000];
    int i = 0;
    while ((lexer_is_alpha(lexer->ch) || lexer_is_digit(lexer->ch)
            || lexer->ch == '-')
           && lexer->pos <= end)
    {
        buffer[i++] = lexer->ch;
        lexer_next_char(lexer);
    }
    buffer[i] = 0;
    lexer->token->value = strdup(buffer);
}

void lexer_word2(struct Lexer *lexer, int end)
{
    char buffer[13000];
    int i = 0;
    while (!isspace2(lexer->ch) && lexer->ch != '\0' && lexer->ch != ';'
           && lexer->ch != '\n' && lexer->ch != '|' && (is_redir(lexer) == 1)
           && lexer->pos <= end)
    {
        buffer[i++] = lexer->ch;
        lexer_next_char(lexer);
    }
    buffer[i] = 0;
    // to be freed
    lexer->token->value = strdup(buffer);
}

void lexer_single_quote(struct Lexer *lexer, int end)
{
    char buffer[13000];
    int i = 0;
    while (lexer->ch != '\'' && lexer->ch != '\0' && lexer->pos <= end)
    {
        buffer[i++] = lexer->ch;
        lexer_next_char(lexer);
    }
    buffer[i] = 0;
    // to be freed
    lexer->token->value = strdup(buffer);
}

// main function
void lexer_next_token(struct Lexer *lexer, int end)
{
    lexer_skip_whitespace(lexer);
    lexer->token->value = NULL;
    if (lexer->ch == '\'')
    {
        single_quotes(lexer, end);
    }
    else if (lexer->ch == '\0')
    {
        lexer_next_char(lexer);
        lexer->token->type = TOKEN_EOF;
    }
    else if (lexer->ch == '#')
    {
        lexer_skip_comment(lexer);
        lexer_next_token(lexer, end);
    }
    else if (lexer_is_digit(lexer->ch) && lexer->option != 1)
    {
        lexer->token->type = TOKEN_IONUMBER;
        lexer_number(lexer);
    }
    else if (lexer_is_alpha(lexer->ch) && lexer->option != 1)
    {
        if_else_more(lexer, end);
    }
    else
    {
        // option = 1
        if (lexer->option == 1)
        {
            option1(lexer, end);
        }
        // option 0 by default : all tokens
        else
        {
            option0(lexer, end);
        }
    }
}

// free function

void free_token(struct Token *token)
{
    if (token->value)
    {
        free(token->value);
    }
}
