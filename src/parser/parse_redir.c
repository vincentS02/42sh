#include "../headers/parse_redir.h"

int is_redir(struct Lexer *lexer)
{
    if (lexer->token->type != TOKEN_GREAT
        && lexer->token->type != TOKEN_DLESSDASH
        && lexer->token->type != TOKEN_GREATAND
        && lexer->token->type != TOKEN_LESSGREAT
        && lexer->token->type != TOKEN_LESSAND
        && lexer->token->type != TOKEN_CLOBBER
        && lexer->token->type != TOKEN_DGREAT
        && lexer->token->type != TOKEN_DLESS
        && lexer->token->type != TOKEN_LESS)
    {
        return 1;
    }
    return 0;
}
int is_redir_left(struct Lexer *lexer)
{
    if (lexer->token->type != TOKEN_DLESSDASH
        && lexer->token->type != TOKEN_LESSAND
        && lexer->token->type != TOKEN_DLESS
        && lexer->token->type != TOKEN_LESS)
    {
        return 1;
    }
    return 0;
}

int is_redir_right(struct Lexer *lexer)
{
    if (lexer->token->type != TOKEN_GREAT
        && lexer->token->type != TOKEN_GREATAND
        && lexer->token->type != TOKEN_CLOBBER
        && lexer->token->type != TOKEN_DGREAT)
    {
        return 1;
    }
    return 0;
}
char *choose_file_redirection(struct Lexer *lexer)
{
    int prev_pos = 0;
    int current_pos = 0;
    char *file;
    while (lexer->token->type != TOKEN_EOF)
    {
        while (is_redir(lexer) == 1)
        {
            prev_pos = lexer->pos;
            lexer_next_token(lexer, lexer->len);
            if (is_redir(lexer) == 1)
                free(lexer->token->value);
        }
        if (is_redir_right(lexer) == 0)
        {
            free(lexer->token->value);
            if (file)
            {
                free(file);
                lexer_next_token(lexer, lexer->len);
                file = strdup(lexer->token->value);
                free(lexer->token->value);
            }
        }
        else
        {
            free(lexer->token->value);
            if (file)
                free(file);
            current_pos = lexer->pos;
            lexer->pos = prev_pos;
            lexer_next_token(lexer, lexer->len);
            file = strdup(lexer->token->value);
            free(lexer->token->value);
            lexer->pos = current_pos;
            lexer_next_token(lexer, lexer->len);
            free(lexer->token->value);
        }
    }
    lexer->pos = prev_pos;
    return file;
}
AstNode *parse_redirection(struct Lexer *lexer, int begin_pos)
{
    lexer->pos = 0;
    lexer->token->type = TOKEN_BEGIN;
    lexer->ch = lexer->input[begin_pos];
    while (is_redir(lexer) == 1)
    {
        lexer_next_token(lexer, lexer->len);
        if (is_redir(lexer) == 1)
            free(lexer->token->value);
    }
    char *token_redirection = strdup(lexer->token->value);
    free(lexer->token->value);
    AstNode *input = parse_simple_command(lexer, lexer->pos, begin_pos);
    AstNode *element = calloc(1, sizeof(AstNode));
    element->type = AST_REDIR;
    element->value = token_redirection;
    element->num_children = 0;
    element->children = NULL;
    begin_pos = lexer->pos;
    add_child(element, input);
    lexer_next_token(lexer, lexer->len);
    free(lexer->token->value);
    while (lexer->token->type != TOKEN_EOF && lexer->token->type != TOKEN_PIPE
           && lexer->token->type != TOKEN_SEMI)
    //(lexer->token->type != TOKEN_EOF)
    {
        rec_parsing_redirection(element, lexer, begin_pos);
    }
    return element;
}
AstNode *rec_parsing_redirection(AstNode *node, struct Lexer *lexer,
                                 int begin_pos)
{
    while (lexer->token->type != TOKEN_EOF && lexer->token->type != TOKEN_PIPE
           && lexer->token->type != TOKEN_SEMI && is_redir(lexer) == 1)
    {
        lexer_next_token(lexer, lexer->len);
        if (is_redir(lexer) == 1)
            free(lexer->token->value);
    }
    if (is_redir(lexer) == 1 || lexer->token->type == TOKEN_PIPE
        || lexer->token->type == TOKEN_SEMI)
    {
        AstNode *output = parse_simple_command(lexer, lexer->pos, begin_pos);
        begin_pos = lexer->pos;
        add_child(node, output);
        return node;
    }
    char *token_redirection = strdup(lexer->token->value);
    free(lexer->token->value);
    AstNode *output = parse_simple_command(lexer, lexer->pos, begin_pos);
    begin_pos = lexer->pos;
    AstNode *element = calloc(1, sizeof(AstNode));
    element->type = AST_REDIR;
    element->value = token_redirection;
    element->num_children = 0;
    element->children = NULL;
    add_child(element, output);
    add_child(node, element);
    lexer_next_token(lexer, lexer->len);
    free(lexer->token->value);
    return rec_parsing_redirection(&node->children[1], lexer, begin_pos);
}
