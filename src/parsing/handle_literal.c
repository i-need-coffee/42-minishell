#include "minishell.h"

int add_arg(char *str, int i, t_pipe_unit *unit)
{
    int start;
    char *substr;

    start = i;
    while(str[i] && (str[i] != ' ' && str[i] != '\'' && str[i] != '\"'))
    {
        i++;
    }
    substr = ft_substr(str, start, i-start);
    create_or_update_lst(unit, substr);
    return(i);
}