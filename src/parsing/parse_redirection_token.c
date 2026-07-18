#include "minishell.h"

int	parse_redirection_token(t_pipe_unit **unit, t_token *current)
{
    if (current->next == NULL) {
        ft_printf(ERR_SYNTAX_TOKEN_REDIRECTION);
        return (-1);
    }
    if (current->next->type != TOKEN_WORD) {
        ft_printf(ERR_SYNTAX_TOKEN_REDIRECTION);
        return (-1);
    }
    if (ft_strncmp(current->value, ">>", 2) == 0) {
        create_or_update_unit_struct(unit, 0, APPEND);
    }
    else if (ft_strncmp(current->value, "<<", 2) == 0)
        return(uptade_unit_struct_heredoc(unit, current));
    else if (current->value[0] == '>')
        create_or_update_unit_struct(unit, 0, REDIR_OUT);
    else if (current->value[0] == '<')
        create_or_update_unit_struct(unit, 1, REDIR_IN);
    else
        return (-1);
    return (0);
}
