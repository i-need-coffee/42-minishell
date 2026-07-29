#include "minishell.h"

int	wrapper_handle_quote(char *str, int *index, t_env *env, char **tmp) // handle error message
{
	int	i;

	i = *(index);
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

int	check_quote_sanity(char *str, int end, char c)//message error handle
{
	while (str[end] && str[end] != c)
		end++;
	if (str[end] != c)
	{
		print_error(ERR_QUOTES);
		return (0);
	}
	return (end);
}

int	handle_double_quote(char *str, int i, t_env *env, char **b) //message error handle
{
	int		start;
	int		end;
	char	*quote_buffer;

	start = i;
	quote_buffer = NULL;
	end = check_quote_sanity(str, i, '\"');
	if (end == 0)
		return (0);
	while (str[i] && !(i > end || i == end))
	{
		if (str[i] == '$')
		{
			if ((create_or_update_buffer(&quote_buffer, str, start, i)) == 0) //message error handle
				return (0);
			if ((i = expension(str, i, env, &quote_buffer)) == 0)//message error handle
				return (0);
			start = i;
			if (i == end)
				start++;
		}
		i++;
	}
	if (start < i)
		if ((create_or_update_buffer(&quote_buffer, str, start, i)) == 0)//message error handle
			return (0);
	*b = quote_buffer;
	return (end + 1);
}

int	handle_single_quote(char *str, int i, char **b) //message error handle
{
	int		end;
	char	*substr;

	i++;
	end = check_quote_sanity(str, i, '\'');
	if (end == 0)
		return (0);
	substr = ft_substr(str, i, end - i);
	if (!substr) {
		print_error(ERR_ALLOC);
		return (0);
	}
	*b = substr;
	end += 1;
	return (end);
}

int	handle_quote(char *str, int i, t_env *env, char **b)// handle message error
{
	if (str[i] == '\"')
		i = handle_double_quote(str, i + 1, env, b);
	else
		i = handle_single_quote(str, i, b);
	if (i == 0)
		return (0);
	return (i);
}
