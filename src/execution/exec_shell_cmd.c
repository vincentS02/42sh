#include "../headers/exec_utils.h"

int execute_rule_if(AstNode *command)
{
    size_t i = 2;
    if (execute_list_command(&command->children[0]) == 0)
    {
        execute_list_command(&command->children[1]);
    }
    else
    {
        if (i < command->num_children)
        {
            while (command->children[i].type == AST_IF)
            {
                if (execute_list_command(&command->children[i].children[0])
                    == 0)
                {
                    execute_list_command(&command->children[i].children[1]);
                    return 0;
                }
                i++;
            }
            execute_list_command(&command->children[i]);
        }
    }
    return 0;
}

int execute_rule_loop(AstNode *command)
{
    if (command->type == AST_WHILE)
    {
        while (execute_list_command(&command->children[0]) == 0)
        {
            execute_list_command(&command->children[1]);
        }
    }
    else if (command->type == AST_UNTIL)
    {
        while (execute_list_command(&command->children[0]) != 0)
        {
            execute_list_command(&command->children[1]);
        }
    }
    else
    {
        return 2;
    }
    return 0;
}
