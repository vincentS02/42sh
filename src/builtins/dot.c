#include "../headers/dot.h"

void dot(const char *file_name)
{
    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error: file %s not found\n", file_name);
        return;
    }
    char command[13000];
    char *args[13000];
    int i;
    while (fgets(command, sizeof(command), file) != NULL)
    {
        i = 0;
        args[i] = strtok(command, " \t\n");
        while (args[i] != NULL)
        {
            i++;
            args[i] = strtok(NULL, " \t\n");
        }
        execvp(args[0], args);
        perror("Error");
    }
    fclose(file);
}
