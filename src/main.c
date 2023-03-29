/* our files */
#include "headers/exec_utils.h"
#include "headers/parse_input.h"

// helper functions

void free_all(struct Lexer *lexer, struct AstNode *ast, char *input)
{
    free_ast(ast);
    free(ast);
    free_lexer_after_free_in_parse(lexer);
    free(input);
}

int print_error(char *string, int err)
{
    fprintf(stderr, "%s\n", string);
    return err;
}

int file_option(char *argv[])
{
    char line[13000];
    long filelen;
    char *input;
    FILE *file = fopen(argv[1], "rb");
    if (!file)
    {
        printf("Could not open file!");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    filelen = ftell(file);
    rewind(file);
    fread(line, filelen, 1, file);
    fclose(file);
    remove_newline(line);
    input = strndup(line, strlen(line));
    struct Lexer *lexer = lexer_init(input);
    struct AstNode *ast = parse_list_command(lexer);
    // grammar error : exit 2 with an error  message
    success(ast); // exit 2 is inside success
    if (ast == NULL)
    {
        free_lexer_after_free_in_parse(lexer);
        free(input);
    }

    int r = execute_list_command(ast);
    // success : true false
    if (r == 5)
        exit(1);
    // error in command
    if (r != 0)
    {
        exit(127);
    }
    free_all(lexer, ast, input);
    return 0;
}

int argument_option(char *input)
{
    // remove last new line
    remove_newline(input);
    if (input[0] == '#' || is_empty_string(input))
    {
        return 0;
    }
    struct Lexer *lexer = lexer_init(input);
    struct AstNode *ast = parse_list_command(lexer);
    // grammar error : exit 2 with an error message
    success(ast); // exit 2 is inside success
    if (ast == NULL)
    {
        free_lexer_after_free_in_parse(lexer);
        free(input);
    }
    int r = execute_list_command(ast);
    // success :true false
    if (r == 5)
        exit(1);
    // error in execute command
    if (r != 0)
    {
        exit(127);
    }
    free_all(lexer, ast, input);
    return 0;
}

int main(int argc, char *argv[])
{
    char *input;
    // ./42sh is entered
    // stdin
    if (argc == 1)
    {
        char line[13000];
        size_t error = 0;
        // parse and execute line by line
        while (fgets(line, 13000, stdin) != NULL)
        {
            // remove last new line
            remove_newline(line);
            if (line[0] == '#' || is_empty_string(line))
            {
                continue;
            }
            input = strndup(line, strlen(line));
            struct Lexer *lexer = lexer_init(input);
            struct AstNode *ast = parse_list_command(lexer);
            // grammar error : exit 2 with an error  message
            success(ast); // exit 2 is inside success
            if (ast == NULL)
            {
                free_lexer_after_free_in_parse(lexer);
                free(input);
            }
            int r = execute_list_command(ast);
            // success : true false
            if (r == 5)
                exit(1);
            // error in command
            if (r != 0)
                exit(127);
            free_all(lexer, ast, input);
            error++;
        }
        // cat error or no stdin
        if (error == 0)
        {
            return 1;
        }
    }
    // other 2 options
    else
    {
        int f = 0;
        int *isfile_op = &f;
        input = get_input(argv, isfile_op);
        // bad argument type
        if (input == NULL && *isfile_op == 0)
        {
            return print_error("Error: Bad Argument Type", -1);
        }
        // can not open file
        if (*isfile_op == 2)
        {
            return print_error("Error: NO file found", 127);
        }

        // file option
        else if (input == NULL && *isfile_op == 1)
        {
            return file_option(argv);
        }
        // -c option
        else
        {
            return argument_option(input);
        }
    }
    // success
    return 0;
}
