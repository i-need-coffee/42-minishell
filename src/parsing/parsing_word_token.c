#include "minishell.h"

// This function parse only word token:
// Start create or add a node in the struct to give back for execution
//
// int add_to_args(t_pipe_unit **head, t_token *current)
// {
//
// }

int    parse_word_token(t_pipe_unit **head, t_token *current, t_env *env)
{
    int i;
    int start;
    t_pipe_unit *new_token;
    char *str;

    str = current->value;
    create_or_update_unit_struct(head, 0, CMD);
    new_token = *head;
    while (new_token->next)
        new_token = new_token->next;
    i = 0;
    start = i;
    while(str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
            i = handle_quote(str, i, env, new_token);
        else if (str[i] == '$')
             i = handle_dollar(str, i, env,new_token);
        else
            i = add_arg(str, i, new_token);
        if (i == -1)
                return (-1);
        while(str[i] == ' ')
            i++;
    }
    return (0);
}
