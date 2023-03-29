#ifndef EXEC_SHELL_CMD_H
#define EXEC_SHELL_CMD_H

#include "exec_utils.h"

int execute_rule_if(AstNode *command);
int execute_rule_loop(AstNode *command);

#endif
