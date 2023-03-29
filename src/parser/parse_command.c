#include "../headers/parse_command.h"

AstNode *parse_simple_command(struct Lexer *lexer, int end, int begin_pos)
{
    init_lexer(lexer, begin_pos, 1);
    AstNode *simple_command = init_root(AST_COMMAND);
    lexer_next_token(lexer, end);
    if (lexer->token->type == TOKEN_DOUBLE_SEMI
        || lexer->token->type == TOKEN_PIPE || lexer->token->type == TOKEN_OR_IF
        || lexer->token->type == TOKEN_TRIPLE_PIPE || is_redir(lexer) == 0
        || lexer->token->type == TOKEN_AMP)
    {
        goto error;
    }
    add_child(simple_command, init_ast(AST_ELEMENT, lexer));
    free_token(lexer->token);
    lexer_next_token(lexer, end);
    if (lexer->token->type == TOKEN_DOUBLE_SEMI
        || lexer->token->type == TOKEN_TRIPLE_PIPE)
    {
        goto error;
    }
    while (lexer->pos < end && lexer->token->type != TOKEN_EOF
           && lexer->token->type != TOKEN_NEWLINE)
    {
        // handle quotes
        if (lexer->token->type == TOKEN_SINGLE_QUOTE)
        {
            remove_single_quotes(lexer->token->value);
        }
        AstNode *element = init_ast(AST_ELEMENT, lexer);
        add_child(simple_command, element);
        free_token(lexer->token);
        lexer_next_token(lexer, end);
        if (lexer->token->type == TOKEN_DOUBLE_SEMI
            || lexer->token->type == TOKEN_TRIPLE_PIPE)
        {
            goto error;
        }
    }
    if (lexer->token->type != TOKEN_EOF && lexer->token->type != TOKEN_SEMI
        && (is_redir(lexer) == 1) && lexer->token->type != TOKEN_PIPE
        && lexer->token->type != TOKEN_NEWLINE)
    {
        add_child(simple_command, init_ast(AST_ELEMENT, lexer));
    }
    lexer->option = 0;
    free_token(lexer->token);
    return simple_command;
error:
    fprintf(stderr, "bash: syntax error near unexpected token : %s\n",
            lexer->token->value);
    cleanup(simple_command, lexer);
    return NULL;
}

void add_child(AstNode *papa, AstNode *son)
{
    if (papa && son)
    {
        papa->num_children++;
        papa->children =
            realloc(papa->children, papa->num_children * sizeof(AstNode));
        papa->children[papa->num_children - 1] = *son;
        free(son);
    }
}

AstNode *new_ast(enum ast_type type)
{
    AstNode *new_ast = calloc(1, sizeof(AstNode));
    new_ast->type = type;
    new_ast->num_children = 0;
    new_ast->children = NULL;
    return new_ast;
}

void init_lexer(struct Lexer *lexer, int begin_pos, int option)
{
    lexer->option = option;
    lexer->pos = begin_pos;
    lexer->token->type = TOKEN_BEGIN;
    lexer->ch = lexer->input[begin_pos];
}
