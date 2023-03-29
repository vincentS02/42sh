#include "../headers/exec_utils.h"

int open_case(char *which_redir_token, char *argv)
{
    int fd = -1;
    if ((strcmp(which_redir_token, ">") == 0)
        || (strcmp(which_redir_token, ">&") == 0)
        || (strcmp(which_redir_token, ">|") == 0))
    {
        fd = open(argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
        if (fd == -1)
        {
            return -1;
        }
    }
    if (strcmp(which_redir_token, ">>") == 0)
    {
        fd = open(argv, O_CREAT | O_APPEND | O_WRONLY, 0644);
        if (fd == -1)
        {
            return -1;
        }
    }
    if (strcmp(which_redir_token, "<>") == 0)
    {
        fd = open(argv, O_CREAT | O_APPEND | O_RDONLY | O_WRONLY, 0644);
        if (fd == -1)
        {
            return -1;
        }
    }
    if ((strcmp(which_redir_token, "<") == 0)
        || (strcmp(which_redir_token, "<&") == 0))
    {
        fd = open(argv, O_CREAT | O_RDONLY);
        if (fd == -1)
        {
            return -1;
        }
    }
    return fd;
}

AstNode *right_most_child(AstNode *node)
{
    AstNode *first = &node->children[1];
    if (first->num_children == 1)
        return first;
    int quit = 0;
    AstNode *tmp = first;
    while (quit == 0)
    {
        AstNode *tmp2 = &tmp->children[1];
        if (!tmp2 && tmp2->num_children == 0)
        {
            fprintf(stderr, "espaces cas malaise\n");
            return 0;
        }
        if (tmp2->num_children == 1)
            return tmp2;
        tmp = &tmp->children[1];
    }
    return 0;
}
AstNode *rec_redir_execution(AstNode *redirection, AstNode *right)
{
    if (redirection->children[0].num_children == 1)
    {
        open_case(redirection->value,
                  redirection->children[0].children[0].value);
    }
    else if ((redirection->num_children == 2)
             && (redirection->type != AST_REDIR))
    {
        return redirection;
    }
    else
    {
        if (redirection->type != AST_REDIR)
            return redirection;
        if (strcmp(redirection->children[0].children[0].value, "echo") == 0)
        {
            AstNode *command = &redirection->children[0];
            const size_t argc = command->num_children;
            char **argv = malloc((argc + 1) * sizeof(char *));
            for (size_t j = 0; j < argc; j++)
            {
                argv[j] = command->children[j].value;
            }
            argv[argc] = NULL;
            FILE *file = fopen(right->children[0].value, "a");
            redir_echo(argc, argv, file);
            free(argv);
            fclose(file);
        }
    }
    return rec_redir_execution(&redirection->children[1], right);
}
int execute_redirection(AstNode *redirection)
{
    // stdout redirection case
    int stdout_dup = dup(STDOUT_FILENO);
    if (stdout_dup == -1)
    {
        goto error;
    }
    AstNode *right = right_most_child(redirection);
    int file_fd = open_case(redirection->value, right->children[0].value);
    // case cringe &>
    int should_restore_stder = 0;
    int stder_fd = -1;
    // &> = redirect both stdout and stder
    if (strcmp(redirection->value, ">&") == 0)
    {
        stder_fd = dup(STDERR_FILENO);
        should_restore_stder = 1;
    }
    // in all cases, dup STDOUT
    if (dup2(file_fd, STDOUT_FILENO) == -1)
    {
        goto error;
    }
    if (should_restore_stder != 0)
    {
        if (dup2(file_fd, STDERR_FILENO) == -1)
        {
            goto error;
        }
    }
    rec_redir_execution(redirection, right);
    // reviens au monde reel
    dup2(stdout_dup, STDOUT_FILENO);
    if (should_restore_stder == 1)
        dup2(stder_fd, STDERR_FILENO);
    close(stdout_dup);
    if (stder_fd != -1)
        close(stder_fd);
    // come back to real life
    return 0;
error:
    fprintf(stderr, "Syscall failed ou erreur quelque part");
    return -1;
}
