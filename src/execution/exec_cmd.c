#include "../headers/exec_utils.h"

// helper functions
int execute_true_false(char **argv)
{
    int tf_result = mytruefalse(argv);
    free(argv);
    return tf_result;
}

void execute_exit(char **argv)
{
    if (argv[1])
        my_exit(atoi(argv[1]), argv);
    my_exit(0, argv);
}

int execute_cd(char **argv)
{
    int a = cd(argv[1]);
    free(argv);
    return a;
}

int execute_command(AstNode *command)
{
    const size_t argc = command->num_children;
    char **argv = malloc((argc + 1) * sizeof(char *));
    for (size_t j = 0; j < argc; j++)
    {
        argv[j] = command->children[j].value;
    }
    argv[argc] = NULL;
    if (strcmp("cd", argv[0]) == 0)
    {
        return execute_cd(argv);
    }
    else if (strcmp("exit", argv[0]) == 0)
    {
        execute_exit(argv);
    }
    else if (strcmp("echo", argv[0]) == 0)
    {
        echo(argc, argv);
        free(argv);
        return 0;
    }
    else if (strcmp("true", argv[0]) == 0 || strcmp("false", argv[0]) == 0)
    {
        return execute_true_false(argv);
    }
    else
    {
        int status = 0;
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Error: fork() failed");
            return 1;
        }
        else if (pid == 0)
        {
            execvp(argv[0], argv);
            perror("Error: execvp() failed");
            _exit(1);
        }
        else
        {
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
        return status;
    }
    return 1;
}
