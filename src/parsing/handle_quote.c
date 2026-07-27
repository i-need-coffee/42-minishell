#include "minishell.h"

int	wrapper_handle_quote(char *str, int *index, t_env *env, char **tmp)
{
	int	i;

	i = *(index);
	if ((handle_quote(str, i, env, tmp)) == -1)
		return (1);
	if (str[i] == '\'')
		*index = check_quote_sanity(str, i + 1, '\'');
	else
		*index = check_quote_sanity(str, i + 1, '\"');
	return (0);
}

int	check_quote_sanity(char *str, int end, char c)
{
	while (str[end] && str[end] != c)
	{
		end++;
	}
	if (str[end] != c)
	{
		print_error(ERR_QUOTES);
		return (-1);
	}
	return (end);
}

int	handle_double_quote(char *str, int i, t_env *env, char **b)
{
	int		start;
	int		end;
	char	*buffer_t_list_args;

	start = i;
	buffer_t_list_args = NULL;
	end = check_quote_sanity(str, i, '\"');
	if (end == -1)
		return (-1);
	while (str[i] && !(i > end || i == end))
	{
		if (str[i] == '$')
		{
			create_or_update_buffer(&buffer_t_list_args, str, start, i);
			i = expension(str, i, env, &buffer_t_list_args);
			start = i;
			if (i == end)
				start++;
		}
		i++;
	}
	if (start < i)
		create_or_update_buffer(&buffer_t_list_args, str, start, i);
	*b = buffer_t_list_args;
	return (end + 1);
}

int	handle_single_quote(char *str, int i, char **b)
{
	int		end;
	char	*substr;

	i++;
	end = check_quote_sanity(str, i, '\'');
	if (end == -1)
		return (-1);
	substr = ft_substr(str, i, end - i);
	*b = substr;
	end += 1;
	return (end);
}

int	handle_quote(char *str, int i, t_env *env, char **b)
{
	if (str[i] == '\"')
		i = handle_double_quote(str, i + 1, env, b);
	else
		i = handle_single_quote(str, i, b);
	if (i == -1)
		return (-1);
	return (i);
}
