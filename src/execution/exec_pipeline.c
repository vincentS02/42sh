#include "../headers/exec_utils.h"

void create_argv(AstNode *node, char ***argv, size_t *argc)
{
    *argc = node->num_children;
    *argv = malloc((*argc + 1) * sizeof(char *));
    for (size_t i = 0; i < *argc; i++)
    {
        (*argv)[i] = node->children[i].value;
    }
    (*argv)[*argc] = NULL;
}

int check1(size_t i, size_t num_commands, int *fd_pipe)
{
    if (i != num_commands - 1)
    {
        if (pipe(fd_pipe) == -1)
        {
            perror("Error: pipe() failed");
            return 1;
        }
    }
    return 0;
}

void check2(int i, int fd_input, int num_commands, int *fd_pipe)
{
    if (i != num_commands - 1)
    {
        close(fd_pipe[1]);
    }
    if (fd_input != 0)
    {
        close(fd_input);
    }
}

void check3(int i, int num_commands, char **argv, int *fd_pipe)
{
    if (i != num_commands - 1)
    {
        if (dup2(fd_pipe[1], 1) == -1)
        {
            perror("Error: dup2() failed");
            _exit(1);
        }
    }
    if (execvp(argv[0], argv) == -1)
    {
        perror("Error: execvp() failed");
        _exit(1);
    }
}

int execute_pipeline(AstNode *pipeline)
{
    const size_t num_commands = pipeline->num_children;
    int fd_pipe[2];
    int fd_input = 0;
    int status = 0;
    for (size_t i = 0; i < num_commands; i++)
    {
        AstNode *command = &pipeline->children[i];
        size_t argc;
        char **argv;
        create_argv(command, &argv, &argc);
        if (check1(i, num_commands, fd_pipe) == 1)
        {
            return 1;
        }
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Error: fork() failed");
            return 1;
        }
        else if (pid == 0)
        {
            if (i == 0)
            {
                fd_input = fd_pipe[0];
            }
            else if (fd_input != 0)
            {
                if (dup2(fd_input, 0) == -1)
                {
                    perror("Error: dup2() failed");
                    _exit(1);
                }
            }
            check3(i, num_commands, argv, fd_pipe);
        }
        else
        {
            check2(i, fd_input, num_commands, fd_pipe);
            fd_input = fd_pipe[0];
            int child_status;
            waitpid(pid, &child_status, 0);
            if (WIFEXITED(child_status))
            {
                int exit_status = WEXITSTATUS(child_status);
                if (exit_status != 0)
                {
                    status = exit_status;
                }
            }
            else
            {
                status = 0;
            }
            free(argv);
        }
    }
    return status;
}
