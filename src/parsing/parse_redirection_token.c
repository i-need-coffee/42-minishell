#include "minishell.h"

char	*put_rest_on_value(char *substr, char *str, int i, char **next_value)
{
	char	*rest;

	rest = NULL;
	substr = ft_substr(str, 0, i);
	rest = ft_substr(str, i, ft_strlen(str) - i);
	free(*next_value);
	*next_value = NULL;
	*next_value = rest;
	return (substr);
}

char	*get_file_name(t_env *env, char **next_value, char *str)
{
	int		i;
	int		start;
	char	*substr;
	char	*tmp;

	i = 0;
	while (str[i] != '\0' && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			start = i;
			substr = ft_substr(str, 0, i);
			if (wrapper_handle_quote(str, &i, env, &tmp))
				return (NULL);
			i = replace_str(&str, tmp, start, i + 1);
			continue ;
		}
		if (str[i] == '$')
		{
			wrapper_handle_dollar(&str, &tmp, &i, env);
			continue ;
		}
		i++;
	}
	return (put_rest_on_value(substr, str, i, next_value));
}

void	wrapper_put_value_in_prev(t_pipe_unit **head, t_token *current,
		t_env *env, t_pipe_unit *current_node)
{
	t_pipe_unit	*tmp_prev;

	tmp_prev = current_node->prev;
	if (ft_strlen(current->next->value) != 0)
	{
		if (!tmp_prev)
		{
			tmp_prev = new_unit_node(0, CMD);
			tmp_prev->prev = NULL;
			tmp_prev->next = current_node;
			current_node->prev = tmp_prev;
			*head = tmp_prev;
		}
		put_value_in_prev_args(tmp_prev, current->next, env);
		clean_str(current->next->value);
	}
}

int	uptade_unit_struct_redir(t_pipe_unit **head, t_token *current, t_env *env,
		t_unit_type type, int cmdi)
{
	t_pipe_unit	*current_node;
	char		*str;
	char		*file_name;

	create_or_update_unit_struct(head, cmdi, type);
	str = current->next->value;
	current_node = *head;
	while (current_node->next)
		current_node = current_node->next;
	file_name = get_file_name(env, &current->next->value, str);
	if (!file_name)
		return (-1);
	create_redirection_node(head, current->next, file_name);
	wrapper_put_value_in_prev(head, current, env, current_node);
	return (0);
}

int	parse_redirection_token(t_pipe_unit **unit, t_token *current, t_env *env,
		int cmdi)
{
	if (current->next == NULL)
	{
		print_error(ERR_REDIR);
		return (-1);
	}
	if (current->next->type != TOKEN_WORD)
	{
		print_error(ERR_REDIR);
		return (-1);
	}
	if (ft_strncmp(current->value, ">>", 2) == 0)
		return (uptade_unit_struct_redir(unit, current, env, APPEND, cmdi));
	else if (ft_strncmp(current->value, "<<", 2) == 0)
		return (uptade_unit_struct_redir(unit, current, env, HEREDOC, cmdi));
	else if (current->value[0] == '>')
		return (uptade_unit_struct_redir(unit, current, env, REDIR_OUT, cmdi));
	else if (current->value[0] == '<')
		return (uptade_unit_struct_redir(unit, current, env, REDIR_IN, cmdi));
	else
		return (-1);
	return (0);
}
