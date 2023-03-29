#ifndef EXIT_H
#define EXIT_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* builtin for EXIT */
void my_exit(int exit_code, char **argv);

#endif
