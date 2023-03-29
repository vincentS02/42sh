#ifndef ECHO_H
#define ECHO_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* builtin for ECHO */
void echo(int argc, char *argv[]);

void redir_echo(int argc, char **argv, FILE *file);

#endif
