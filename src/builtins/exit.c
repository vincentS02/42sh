#include "../headers/exit.h"

void my_exit(int exit_code, char **argv)
{
    if (!argv[1])
    {
        exit(0);
    }
    if (!argv[2])
    {
        free(argv);
        exit(exit_code);
    }
    else
    {
        perror("exit: trop d'arguments\n");
    }
}
