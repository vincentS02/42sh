#include "headers/utilities.h"

#include "headers/lexer.h"

int is_empty_string(const char *str)
{
    if (strlen(str) == 0)
    {
        return 1;
    }
    int i = 0;
    int len = strlen(str);
    while (i < len)
    {
        if (!isspace(str[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

// remove last new line form stdin
void remove_newline(char *string)
{
    int len = strlen(string);
    if (string[len - 1] == '\n')
    {
        string[len - 1] = '\0';
    }
}

// case of 'ls'
int is_delimited_by_single_quotes(const char *str)
{
    int len = strlen(str);
    return len >= 2 && str[0] == '\'' && str[len - 1] == '\'';
}

void remove_single_quotes(char *str)
{
    size_t len = strlen(str);
    if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
    {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

int is_command(struct Lexer *lexer, int begin, int end)
{
    lexer_skip_whitespace(lexer);
    char path[13000];
    int i = 0;
    while (!isspace2(lexer->ch) && lexer->ch != '\0' && lexer->pos <= end)
    {
        path[i++] = lexer->ch;
        lexer_next_char(lexer);
    }
    path[i] = 0;
    // to be freed
    int r = is_delimited_by_single_quotes(path);
    if (access(path, X_OK) == 0 || r == 1)
    {
        if (r == 1)
        {
            remove_single_quotes(path);
        }
        lexer->token->value = strdup(path);
        lexer_next_char(lexer);
        lexer->token->type = TOKEN_COMMAND;
        return 1;
    }
    lexer->token->value = NULL;
    lexer->pos = begin;
    lexer->ch = lexer->input[begin];

    return 0;
}

int isNumber(char c)
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }
    return 0;
}
