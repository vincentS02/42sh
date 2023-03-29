#include "../headers/parse_pipeline.h"

int has_pipe(const char *str, size_t end)
{
    size_t i = 0;
    while (i < strlen(str) && i < (size_t)end)
    {
        if (str[i] == '|')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

AstNode *parse_pipeline(struct Lexer *lexer, int end, int begin_pos)
{
    // Init the lexer
    init_lexer(lexer, begin_pos, 0);
    // Init the AST
    AstNode *pipeline = init_root(AST_PIPELINE);
    // loop through commands seperated by |
    while (lexer->token->type != TOKEN_SEMI && lexer->token->type != TOKEN_EOF
           && lexer->pos < end)
    {
        while (lexer->token->type != TOKEN_PIPE && lexer->pos < end)
        {
            lexer_next_token(lexer, end);
            free_token(lexer->token);
        }
        AstNode *child = parse_simple_command(lexer, lexer->pos, begin_pos);
        // grammar error
        if (child == NULL)
        {
            root_cleanup(pipeline);
            return NULL;
        }
        add_child(pipeline, child);
        begin_pos = lexer->pos;
        lexer_next_token(lexer, end);
        free_token(lexer->token);
    }
    // free_token(lexer->token);
    return pipeline;
}
