#include "../headers/parse_shell_command.h"

int skip_newline(struct Lexer *lexer, int begin_pos)
{
    while (lexer->token->type == TOKEN_NEWLINE)
    {
        begin_pos = lexer->pos;
        lexer_next_token(lexer, lexer->len);
        if (lexer->token->value)
        {
            free(lexer->token->value);
        }
    }
    return begin_pos;
}

void one_line_free(AstNode *ast)
{
    free_ast(ast);
    free(ast);
}

void lexer_next_free(struct Lexer *lexer)
{
    lexer_next_token(lexer, lexer->len);
    if (lexer->token->value)
        free(lexer->token->value);
}

int is_good(enum TokenType next, struct Lexer *lexer)
{
    if (lexer->token->type != next
        && !(next == TOKEN_ELSE
             && (lexer->token->type == TOKEN_ELIF
                 || lexer->token->type == TOKEN_FI))
        && lexer->token->type != TOKEN_EOF)
    {
        return 1;
    }
    return 0;
}

int while_end(struct Lexer *lexer, int first)
{
    while (lexer->token->type != TOKEN_SEMI
           && lexer->token->type != TOKEN_NEWLINE
           && lexer->token->type != TOKEN_EOF)
    {
        first++;
        lexer_next_free(lexer);
    }
    return first;
}

AstNode *parse_compound_list(struct Lexer *lexer, int begin_pos,
                             enum TokenType next)
{
    init_lexer(lexer, begin_pos, lexer->option);
    lexer_next_free(lexer);
    begin_pos = skip_newline(lexer, begin_pos);
    AstNode *compound_list = new_ast(AST_LIST);
    int first = 0;
    int isarg = 0;
    while (is_good(next, lexer) == 1)
    {
        isarg++;
        if (first == 0)
        {
            switch (lexer->token->type)
            {
            case TOKEN_IF:
                add_child(compound_list, parse_if(lexer, begin_pos));
                begin_pos = lexer->pos;
                lexer_next_free(lexer);
                continue;
            case TOKEN_WHILE:
            case TOKEN_UNTIL:
                add_child(compound_list,
                          parse_loop(lexer, begin_pos, lexer->token->type));
                begin_pos = lexer->pos;
                lexer_next_free(lexer);
                continue;
            default:
                break;
            }
        }
        first = while_end(lexer, first);
        AstNode *command = parse_simple_command(lexer, lexer->pos, begin_pos);
        if (command == NULL)
        {
            one_line_free(command);
            return NULL;
        }
        add_child(compound_list, command);
        begin_pos = lexer->pos;
        lexer_next_free(lexer);
        first = 0;
        begin_pos = skip_newline(lexer, begin_pos);
    }
    if (lexer->token->type == TOKEN_EOF || isarg == 0)
    {
        one_line_free(compound_list);
        return NULL;
    }
    return compound_list;
}

int parse_elif(struct Lexer *lexer, AstNode *if_command, int begin_pos,
               AstNode *then)
{
    while (lexer->token->type == TOKEN_ELIF)
    {
        AstNode *elif_command = new_ast(AST_IF);
        AstNode *elif_condition =
            parse_compound_list(lexer, begin_pos, TOKEN_THEN);
        if (then == NULL)
        {
            return -1;
        }
        add_child(elif_command, elif_condition);
        lexer_next_token(lexer, lexer->len);
        skip_newline(lexer, begin_pos);
        begin_pos = lexer->pos;
        // parse then
        AstNode *elif_then = parse_compound_list(lexer, begin_pos, TOKEN_ELSE);
        add_child(elif_command, elif_then);
        begin_pos = lexer->pos;
        add_child(if_command, elif_command);
    }
    return begin_pos;
}

AstNode *parse_if(struct Lexer *lexer, int begin_pos)
{
    lexer->pos = begin_pos;
    lexer->ch = lexer->input[begin_pos];
    // parse if
    AstNode *if_command = new_ast(AST_IF);
    lexer_next_free(lexer);
    begin_pos = lexer->pos;
    AstNode *if_condition = parse_compound_list(lexer, begin_pos, TOKEN_THEN);
    if (if_condition == NULL)
    {
        goto error;
    }
    add_child(if_command, if_condition);
    skip_newline(lexer, begin_pos);
    begin_pos = lexer->pos;
    // parse then
    AstNode *then = parse_compound_list(lexer, begin_pos, TOKEN_ELSE);
    if (then == NULL)
    {
        goto error;
    }
    add_child(if_command, then);
    begin_pos = lexer->pos;
    // parse elif
    begin_pos = parse_elif(lexer, if_command, begin_pos, then);
    if (begin_pos == -1)
    {
        goto error;
    }
    if (lexer->token->type == TOKEN_ELSE)
    {
        AstNode *rule_else = parse_compound_list(lexer, lexer->pos, TOKEN_FI);
        add_child(if_command, rule_else);
        begin_pos = lexer->pos;
    }
    skip_newline(lexer, begin_pos);
    if (lexer->token->type != TOKEN_FI)
    {
        goto error;
    }
    lexer_next_free(lexer);
    return if_command; // if_base;
error:
    fprintf(stderr, "Error: got unexpected token '%s' \n", lexer->token->value);
    one_line_free(if_command);
    free_lexer_after_free_in_parse(lexer);
    return NULL;
}

AstNode *parse_loop(struct Lexer *lexer, int begin_pos, enum TokenType ttype)
{
    lexer->pos = begin_pos;
    lexer->ch = lexer->input[begin_pos];
    enum ast_type type;
    if (ttype == TOKEN_WHILE)
    {
        type = AST_WHILE;
    }
    else
    {
        type = AST_UNTIL;
    }
    // parse condition
    AstNode *loop_command = new_ast(type);
    lexer_next_token(lexer, lexer->len);
    if (lexer->token->value)
    {
        free(lexer->token->value);
    }
    begin_pos = lexer->pos;
    AstNode *loop_condition = parse_compound_list(lexer, begin_pos, TOKEN_DO);
    if (loop_condition == NULL)
    {
        fprintf(stderr, "Error syntax, got unexpected token '%d' \n",
                lexer->token->type);
        one_line_free(loop_command);
        return NULL;
    }
    add_child(loop_command, loop_condition);
    skip_newline(lexer, begin_pos);
    begin_pos = lexer->pos;
    AstNode *command = parse_compound_list(lexer, begin_pos, TOKEN_DONE);
    if (command == NULL)
    {
        fprintf(stderr, "Error syntax, got unexpected token '%d' \n",
                lexer->token->type);
        one_line_free(loop_command);
        return NULL;
    }
    add_child(loop_command, command);
    return loop_command;
}
