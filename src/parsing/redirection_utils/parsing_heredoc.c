#include "minishell.h"


static int	internal_check_quote_sanity(char *str, int end, char c)
{
    while (str[end] && str[end] != c)
        end++;
    if (str[end] != c)
        return (-1);
    return (end);
}

static int  handle_literal_argument(t_pipe_unit **unit, t_token *next) {
    int end;
    char    *buffer;
    char    *tmp;

    end = internal_check_quote_sanity(next->value, 1, '\"');
    if (end == -1 )
        return (-1);
    //TODO: gerer le cas ou != ' '. genre "infile".txt
    (*unit)->file = ft_substr(next->value, 1, end - 1);
    buffer = ft_substr(next->value, end + 1, ft_strlen(next->value) - end);
    tmp = ft_strtrim(buffer, " ");
    free(next->value);
    free(buffer);
    next->value = tmp;
    return (0);
}

static int handle_single_argument(t_pipe_unit **unit, t_token *next) {
    int end;
    char    *buffer;
    char    *tmp;

    end = 0;
    while (next->value[end] && next->value[end] != ' ')
        end++;
    //TODO: gerer le cas ou != ' '. genre "infile".txt
    (*unit)->file = ft_substr(next->value, 0, end);
    buffer = ft_substr(next->value, end + 1, ft_strlen(next->value) - end);
    tmp = ft_strtrim(buffer, " ");
    free(next->value);
    free(buffer);
    next->value = tmp;
    return (0);
}

int uptade_unit_struct_heredoc(t_pipe_unit **unit, t_token *current) {
    create_or_update_unit_struct(unit, 0, HEREDOC);
    if (current->next->value[0] == '"')
    {
        if (handle_literal_argument(unit, current->next))
        {
            ft_printf(ERR_SYNTAX_TOKEN_REDIRECTION);
            return (-1);
        }
    }
    else
        handle_single_argument(unit, current->next);
    return (0);
}