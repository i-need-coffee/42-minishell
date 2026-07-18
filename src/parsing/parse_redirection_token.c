#include "minishell.h"

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

int uptade_unit_struct_redir_out(t_pipe_unit **head, t_token *current, t_env *env, t_unit_type type) {
    create_or_update_unit_struct(head, 0, type);
    t_pipe_unit *current_node;

    current_node = *head;
    while (current_node->next)
        current_node = current_node->next;
    if (current->next->value[0] == '"') {
        if (handle_literal_argument(head, current->next))
        {
            ft_printf(ERR_SYNTAX_TOKEN_REDIRECTION);
            return (-1);
        }
    }
    else
        handle_single_argument(head, current->next);
    if (ft_strlen(current->next->value) != 0) {
        put_value_in_prev_args(current_node->prev, current->next, env);
        clean_str(current->next->value);
    }
    return (0);
}

int	parse_redirection_token(t_pipe_unit **unit, t_token *current, t_env *env)
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
        // if (current->value[3] == '>' )
            // TODO: bash: syntax error near unexpected token `>>'
            return(uptade_unit_struct_redir_out(unit, current, env, APPEND));
    }
    else if (ft_strncmp(current->value, "<<", 2) == 0)
        return(uptade_unit_struct_heredoc(unit, current));
    else if (current->value[0] == '>')
        return(uptade_unit_struct_redir_out(unit, current, env, REDIR_OUT));
    else if (current->value[0] == '<')
        return(uptade_unit_struct_redir_out(unit, current, env, REDIR_IN));
    else
        return (-1);
    return (0);
}
