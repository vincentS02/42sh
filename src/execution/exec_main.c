#include "../headers/exec_utils.h"

int execute_list_command(AstNode *node)
{
    size_t numc = 1;
    int res;
    int fils = 1;
    if (node->type == AST_LIST)
    {
        numc = node->num_children;
        fils = 0;
    }
    for (size_t i = 0; i < numc; i++)
    {
        AstNode *command;
        if (fils == 0)
            command = &node->children[i];
        else
            command = node;
        switch (command->type)
        {
        case AST_COMMAND:
            res = execute_command(command);
            break;
        case AST_IF:
            res = execute_rule_if(command);
            break;
        case AST_WHILE:
        case AST_UNTIL:
            res = execute_rule_loop(command);
            break;
        case AST_REDIR:
            res = execute_redirection(command);
            break;
        case AST_LIST:
            res = execute_list_command(command);
            break;
        case AST_PIPELINE:
            res = execute_pipeline(command);
            break;
        default:
            fprintf(
                stderr,
                "Error: expected AST of type AST_COMMAND or AST_IF, got %d\n",
                command->type);
            return 1;
        }
        // Convert the command and its arguments to a null-terminated array
    }
    return res;
}
