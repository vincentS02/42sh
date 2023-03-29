project('42sh', 'c',
                version: '0')
add_global_arguments('-Wall', language : 'c')
add_global_arguments('-Werror', language : 'c')
add_global_arguments('-pedantic', language : 'c')
add_global_arguments('-std=c99', language : 'c')
add_global_arguments('-g', language : 'c')
add_global_arguments('-fsanitize=address', language : 'c')
add_global_arguments('-Wextra', language : 'c')
add_global_arguments('-Wvla', language : 'c')
add_global_link_arguments('-fsanitize=address', language : 'c')
executable('42sh', 'src/main.c', 
        'src/parser/parser.c', 'src/lexer/lexer.c',
            'src/free_functions.c' , 
                'src/parser/parse_input.c' , 'src/parser/print_ast.c' ,
                     'src/free_functions.c', 
                        'src/utilities.c','src/parser/parse_pipeline.c',
                           'src/parser/parse_command.c', 'src/parser/parse_shell_command.c',
                               'src/execution/exec_cmd.c', 'src/execution/exec_main.c',
                                  'src/execution/exec_pipeline.c' , 'src/execution/exec_shell_cmd.c',
                                   'src/execution/execute_utils.c' , 'src/builtins/cd.c' ,
                                   'src/execution/exec_redir.c', 'src/parser/parse_redir.c',
                                   'src/builtins/dot.c' ,'src/builtins/echo.c', 
                                   'src/builtins/exit.c','src/builtins/true_false.c',
                                   'src/lexer/lexer_helper1.c', 'src/lexer/lexer_helper2.c')  