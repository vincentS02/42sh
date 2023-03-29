#include "../headers/true_false.h"

int mytruefalse(char *argv[])
{
    if (strcmp(argv[0], "true") == 0)
        return 0;
    return 5;
}
