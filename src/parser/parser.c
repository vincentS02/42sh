#include "../headers/parser.h"

#include "../headers/all_parsers.h"
// lexer_option is 0 by default

AstNode *init_ast(enum ast_type type, struct Lexer *lexer)
{
    AstNode *node = malloc(sizeof(struct AstNode));
    if (node == NULL)
    {
        return NULL;
    }
    node->type = type;
    if (lexer->token->value)
    {
        node->value = strdup(lexer->token->value);
    }
    node->num_children = 0;
    node->children = NULL;
    return node;
}
AstNode *init_root(enum ast_type type)
{
    AstNode *node = calloc(1, sizeof(AstNode));
    ;
    if (node == NULL)
    {
        return NULL;
    }
    node->type = type;
    node->num_children = 0;
    node->children = NULL;
    return node;
}

void cleanup(struct AstNode *node, struct Lexer *lexer)
{
    free(lexer->token->value);
    lexer->option = 0;
    for (size_t i = 0; i < node->num_children; i++)
    {
        free(node->children[i].value);
    }
    free(node->children);
    free(node);
}
void root_cleanup(struct AstNode *node)
{
    for (size_t i = 0; i < node->num_children; i++)
    {
        free(node->children[i].value);
    }
    free(node->children);
    free(node);
}

int ends(char *string, int end)
{
    char *ends[] = { "<<", "<", ">>", ">", ">|", ">&", "<&", "<>" };
    int len = strlen(string);
    if (len < 2)
        return 0;
    char buffer[3] = { string[len - 2], string[len - 1], '\0' };
    end = 8;
    for (int i = 0; i < end; i++)
    {
        if (buffer[0] != '\0')
        {
            if ((strcmp(buffer, ends[i]) == 0) || (buffer[1] == '>')
                || (buffer[1] == '<'))
                return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

int isthere(char *string, int end)
{
    int i;
    for (i = 0; i < end - 1; i++)
    {
        if (string[i] == '|')
        {
            i++;
            while (string[i] == ' ')
            {
                i++;
            }
            if (string[i] == '|')
            {
                return 1;
            }
        }
    }
    return 0;
}

int in_while(struct Lexer *lexer)
{
    if (lexer->token->type != TOKEN_SEMI && (is_redir(lexer) != 0)
        && lexer->token->type != TOKEN_NEWLINE
        && lexer->token->type != TOKEN_EOF)
        return 1;
    return 0;
}

int add_pos_free(struct Lexer *lexer, AstNode *list_command, AstNode *command)
{
    add_child(list_command, command);
    int i = lexer->pos;
    lexer_next_free(lexer);
    return i;
}

AstNode *error_cmd(AstNode *list_command)
{
    fprintf(stderr, "bash: syntax error : unexpected error \n");
    free(list_command);
    return NULL;
}
/////////main parser////////////
AstNode *parse_list_command(struct Lexer *lexer)
{
    int begin_pos = 0;
    AstNode *list_command = new_ast(AST_LIST);
    while (lexer->token->type != TOKEN_EOF)
    {
        enum TokenType type = TOKEN_BEGIN;
        AstNode *command;
        size_t i = 0;
        while (in_while(lexer) == 1)
        {
            if (lexer->token->type != TOKEN_BEGIN && type == TOKEN_BEGIN)
                type = lexer->token->type;
            lexer_next_token(lexer, lexer->len);
            // ICI
            if (lexer->token->value)
            {
                free(lexer->token->value);
            }
            i++;
        }
        if (i == 1 && lexer->token->type == TOKEN_SEMI)
        {
            return error_cmd(list_command);
        }
        switch (type)
        {
        case TOKEN_IF:
            command = parse_if(lexer, begin_pos);
            break;
        case TOKEN_WHILE:
        case TOKEN_UNTIL:
            command = parse_loop(lexer, begin_pos, type);
            break;
        default:
            if (is_redir(lexer) == 0)
            {
                if (ends(lexer->input, lexer->len))
                {
                    return error_cmd(list_command);
                }
                command = parse_redirection(lexer, begin_pos);
            }
            else if (has_pipe(lexer->input, lexer->pos))
            {
                if (isthere(lexer->input, lexer->len))
                {
                    return error_cmd(list_command);
                }
                command = parse_pipeline(lexer, lexer->pos, begin_pos);
            }
            else
            {
                command = parse_simple_command(lexer, lexer->pos, begin_pos);
            }
            break;
        }
        if (command == NULL)
        {
            return error_cmd(list_command);
        }
        begin_pos = add_pos_free(lexer, list_command, command);
    }
    return list_command;
}
