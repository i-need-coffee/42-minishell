#include "minishell.h"

int uptade_unit_struct_heredoc(t_pipe_unit **unit, t_token *current) {
    create_or_update_unit_struct(unit, 0, HEREDOC);
    if (current->next->value[0] == '"')
    {
        // TODO: look at `uptade_unit_struct_redir_out`
        return 0;
    }
    return (0);
}

char *get_file_name( t_env *env, char **next_value, char *str) {
    int i;
    int start;
    int replace_start;
    char *substr;
    char *tmp;
    char *rest;

    rest = NULL;
    start = 0;
    i = 0;
    while (str[i] != '\0' && str[i] != ' ') {
        if (str[i] == '\'' || str[i] == '\"') {
            replace_start = i;
            substr = ft_substr(str,start ,i - start );
            if ((handle_quote(str, i, env, &tmp)) == -1) // changement, effacement de ret
                return (NULL);
            if (str[i] == '\'')
                i = check_quote_sanity(str, i + 1, '\'');
            else
                i = check_quote_sanity(str, i + 1, '\"');
            i = replace_str(&str, tmp, replace_start, i + 1);
            continue;
        }
        if (str[i] == '$') {
            replace_start = i;
            i = handle_dollar(str, i, env, &tmp);
            i = replace_str(&str, tmp, replace_start, i);
            continue;
        }
        i++;
    }
    substr = ft_substr(str, start, i - start);
    rest = ft_substr(str, i, ft_strlen(str) - i);
    free(*next_value);
    *next_value = NULL;
    *next_value = rest;
    return (substr);
}

int uptade_unit_struct_redir(t_pipe_unit **head, t_token *current, t_env *env, t_unit_type type) {
    create_or_update_unit_struct(head, 0, type);
    t_pipe_unit *current_node;
    t_pipe_unit *tmp_prev;
    char *str = current->next->value;
    char *file_name;

    current_node = *head;
    while (current_node->next)
        current_node = current_node->next;
    tmp_prev = current_node->prev;
    file_name = get_file_name(env, &current->next->value, str);
    if (!file_name)
        return (-1);
    create_redirection_node(head, current->next, file_name);
    if (ft_strlen(current->next->value) != 0) {
        if (!tmp_prev) {
            tmp_prev = new_unit_node(0, CMD);
            tmp_prev->prev = NULL;
            tmp_prev->next = current_node;
            current_node->prev = tmp_prev;
            *head = tmp_prev;
        }
        put_value_in_prev_args(tmp_prev, current->next, env);
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
            return(uptade_unit_struct_redir(unit, current, env, APPEND));
    }
    else if (ft_strncmp(current->value, "<<", 2) == 0)
        return(uptade_unit_struct_redir(unit, current,env, HEREDOC));
    else if (current->value[0] == '>')
        return(uptade_unit_struct_redir(unit, current, env, REDIR_OUT));
    else if (current->value[0] == '<')
        return(uptade_unit_struct_redir(unit, current, env, REDIR_IN));
    else
        return (-1);
    return (0);
}
