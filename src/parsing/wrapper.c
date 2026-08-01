#include "minishell.h"

int	wrapper_update_buffer(char *buffer, char *str, int start, int buff_len)
{
	char	*substr;
	char	*tmp_buffer;

	tmp_buffer = (char *)malloc(ft_strlen(buffer) + 1);
	if (!tmp_buffer)
	{
		print_error(ERR_ALLOC);
		return (0);
	}
	ft_strlcpy(tmp_buffer, buffer, (ft_strlen(buffer) + 1));
	free(buffer);
	substr = ft_substr(str, start, buff_len);
	if (!substr)
	{
		print_error(ERR_ALLOC);
		return (0);
	}
	buffer = ft_strjoin(tmp_buffer, substr);
	if (!buffer)
	{
		print_error(ERR_ALLOC);
		return (0);
	}
	free(substr);
	return (free(tmp_buffer), 1);
}

int	wrapper_handle_quote(char *str, int *index, t_env *env, char **tmp)
{
	int	i;

	i = *index;
	if ((handle_quote(str, i, env, tmp)) == 0)
		return (0);
	if (str[i] == '\'')
		*index = check_quote_sanity(str, i + 1, '\'');
	else
		*index = check_quote_sanity(str, i + 1, '\"');
	if (*index == 0)
		return (0);
	return (1);
}

int	wrapper_put_value_in_prev(t_pipe_unit **head, t_token *current, t_env *env,
		t_pipe_unit *current_node)
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
		if (!(put_value_in_prev_args(tmp_prev, current->next, env)))
			return (0);
		clean_str(current->next->value);
	}
	return (1);
}

int	wrapper_coub(char **quote_buffer, char *str, int start, int i)
{
	if (start < i)
	{
		if ((create_or_update_buffer(quote_buffer, str, start, i)) == 0)
			return (0);
	}
	return (1);
}
