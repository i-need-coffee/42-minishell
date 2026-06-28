#include "minishell.h"



int    parse_word_token(t_pipe_unit **head, char *str, int cmdi, t_env *env)
{
    int i;
    t_pipe_unit *new_token;

    create_or_update_unit_struct(head, cmdi, CMD);
    new_token = *head;
    i = 0;
    while(str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            i = handle_quote(str, i, env, new_token);
            if (i == -1)
                return (-1);
        }
        // else if (str[i] == '$')
            // handle_dollard_withou_quote()
        else
            i = add_arg(str, i, new_token);
        while(str[i] == ' ')
            i++;
    }
    return (0);
}
