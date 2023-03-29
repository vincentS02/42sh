#define _POSIX_C_SOURCE 200809L
#include "../headers/parse_input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_input(char *argv[], int *isfile)
{
    char *input;
    FILE *file;
    char line[9000];
    int entered = 0;
    int boolean = 0;
    if (strcmp(argv[1], "--pretty-print") == 0)
    {
        boolean = 1;
    }
    // consider input as string
    if (strncmp(argv[1 + boolean], "-c", 2) == 0)
    {
        *isfile = 0;
        entered = 1;
        file = fmemopen(argv[2 + boolean], strlen(argv[2 + boolean]), "r");
        if (file == NULL)
        {
            goto error;
        }

        fgets(line, 9000, file);
        input = strndup(line, strlen(line));
        fclose(file);
        return input;
    }
    // case with ./42sh script.sh
    else if (entered == 0 && argv[2] == NULL)
    {
        *isfile = 1;
        file = fopen(argv[1 + boolean], "r");
        if (file == NULL)
        {
            *isfile = 2;
            goto error;
        }
        fclose(file);
        return NULL;
    }
    // error : ex : ./42sh -d ckckcc (3 argument error)
    return NULL;
error:
    return NULL;
}
