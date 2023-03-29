#include "../headers/echo.h"

void echo(int argc, char *argv[])
{
    int i = 0;
    int e_flag = 0;
    int n_flag = 0;
    int E_flag = 0;
    E_flag--;

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-e") == 0)
        {
            e_flag = 1;
        }
        else if (strcmp(argv[i], "-n") == 0)
        {
            n_flag = 1;
        }
        else if (strcmp(argv[i], "-E") == 0)
        {
            E_flag = 1;
        }
        else
        {
            break;
        }
    }
    int l = 0;
    while (argv[i][l] == 39)
    {
        l++;
    }
    for (; i < argc; i++)
    {
        if (e_flag)
        {
            for (int j = 0; argv[i][j] != '\0'; j++)
            {
                if (argv[i][j] == '\\' && argv[i][j + 1] == 't')
                {
                    putchar('\t');
                    j++;
                }
                else if (argv[i][j] == '\\' && argv[i][j + 1] == 'n')
                {
                    putchar('\n');
                    j++;
                }
                else if (argv[i][j] == '\\' && argv[i][j + 1] == '\\')
                {
                    putchar('\\');
                    j++;
                }
                else
                {
                    putchar(argv[i][j]);
                }
            }
        }
        else
        {
            for (int j = 0; argv[i][j] != '\0'; j++)
            {
                putchar(argv[i][j]);
            }
        }

        if (i < argc - 1 && !n_flag)
        {
            putchar(' ');
        }
    }
    if (!n_flag)
    {
        putchar('\n');
    }
}

void redir_echo(int argc, char **argv, FILE *file)
{
    int i = 0;
    int e_flag = 0;
    int n_flag = 0;
    int E_flag = 0;
    E_flag--;

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-e") == 0)
        {
            e_flag = 1;
        }
        else if (strcmp(argv[i], "-n") == 0)
        {
            n_flag = 1;
        }
        else if (strcmp(argv[i], "-E") == 0)
        {
            E_flag = 1;
        }
        else
        {
            break;
        }
    }
    int l = 0;
    while (argv[i][l] == 39)
    {
        l++;
    }
    for (; i < argc; i++)
    {
        if (e_flag)
        {
            for (int j = 0; argv[i][j] != '\0'; j++)
            {
                if (argv[i][j] == '\\' && argv[i][j + 1] == 't')
                {
                    putc('\t', file);
                    j++;
                }
                else if (argv[i][j] == '\\' && argv[i][j + 1] == 'n')
                {
                    putc('\n', file);
                    j++;
                }
                else if (argv[i][j] == '\\' && argv[i][j + 1] == '\\')
                {
                    putc('\\', file);
                    j++;
                }
                else
                {
                    putc(argv[i][j], file);
                }
            }
        }
        else
        {
            for (int j = 0; argv[i][j] != '\0'; j++)
            {
                putc(argv[i][j], file);
            }
        }

        if (i < argc - 1 && !n_flag)
        {
            putc(' ', file);
        }
    }
    if (!n_flag)
    {
        putc('\n', file);
    }
}
