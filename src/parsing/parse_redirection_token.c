#include "minishell.h"

char	*put_rest_on_value(char **str, int i, char **next_value)
{
	char	*rest;
	char	*substr;

	rest = NULL;
	substr = NULL;
	substr = ft_substr(*str, 0, i);
	if (!substr)
	{
		print_error(ERR_ALLOC);
		return (NULL);
	}
	rest = ft_substr(*str, i, ft_strlen(*str) - i);
	if (!rest)
	{
		print_error(ERR_ALLOC);
		free(substr);
		substr = NULL;
		return (NULL);
	}
	free(*next_value);
	*next_value = NULL;
	*next_value = rest;
	return (substr);
}

int	quote_part(char **str, int *i, t_env *env)
{
	char	*substr;
	char	*tmp;
	int		start;

	start = 0;
	tmp = NULL;
	substr = NULL;
	start = *i;
	substr = ft_substr(*str, 0, *i);
	if (!substr)
	{
		print_error(ERR_ALLOC);
		return (0);
	}
	if (!(wrapper_handle_quote(*str, i, env, &tmp)))
		return (0);
	*i = replace_str(str, tmp, start, *(i) + 1);
	free(tmp);
	tmp = NULL;
	free(substr);
	substr = NULL;
	if (*i == 0)
		return (0);
	return (1);
}

char	*get_file_name(t_env *env, char **next_value, char **str)
{
	int		i;
	char	*tmp_str;
	char	*substr;

	i = 0;
	tmp_str = *str;
	substr = NULL;
	while (tmp_str[i] != '\0' && tmp_str[i] != ' ')
	{
		if (tmp_str[i] == '\'' || tmp_str[i] == '\"')
		{
			if (!quote_part(&tmp_str, &i, env))
				return (NULL);
			continue ;
		}
		if (tmp_str[i] == '$')
		{
			if (!(wrapper_handle_dollar(&tmp_str, &i, env)))
				return (NULL);
			continue ;
		}
		i++;
	}
	substr = put_rest_on_value(&tmp_str, i, next_value);
	return (substr);
}

int	uptade_unit_struct_redir(t_mini *mini, t_token *current, t_unit_type type,
		int cmdi)
{
	t_pipe_unit	*current_node;
	char		*str;
	char		*file_name;
	t_pipe_unit	**head;

	head = &mini->units;
	if (!(create_or_update_unit_struct(head, cmdi, type)))
		return (0);
	str = ft_strdup(current->next->value);
	if (!str)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	current_node = *head;
	while (current_node->next)
		current_node = current_node->next;
	file_name = get_file_name(mini->env, &current->next->value, &str);
	if (!file_name)
		return (free_and_null(&str), 0);
	if (!(create_redirection_node(head, current->next, file_name)))
		return (free_and_null(&str), 0);
	if (!(wrapper_put_value_in_prev(head, current, mini->env, current_node)))
		return (free_and_null(&str), 0);
	free_and_null(&str);
	return (1);
}

int	parse_redirection_token(t_pipe_unit **unit, t_token *current, t_mini *mini,
		int cmdi)
{
	(void)unit;
	if (current->next == NULL)
		ft_abort("errno");
	if (current->next->type != TOKEN_WORD)
		ft_abort("errno");
	if (ft_strncmp(current->value, ">>", 2) == 0)
		return (uptade_unit_struct_redir(mini, current, APPEND, cmdi));
	else if (ft_strncmp(current->value, "<<", 2) == 0)
		return (uptade_unit_struct_redir(mini, current, HEREDOC, cmdi));
	else if (current->value[0] == '>')
		return (uptade_unit_struct_redir(mini, current, REDIR_OUT, cmdi));
	else if (current->value[0] == '<')
		return (uptade_unit_struct_redir(mini, current, REDIR_IN, cmdi));
	else
		return (0);
	return (1);
}
