#include "minishell.h"

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

int	handle_double_quote(char *str, int i, t_env *env, t_pipe_unit *unit)
{
	int		start;
	int		end;
	char	*buffer;

	start = i;
	buffer = NULL;
	end = check_quote_sanity(str, i, '\"');// error message to add
	if (end == -1)
		return (-1);
	while (str[i] && !(i > end || i == end))
	{
		if (str[i] == '$')
		{
			create_or_update_buffer(&buffer, str, start, i);
			i = handle_dollard(str, i, env, &buffer);
			start = i;
			if (i == end)
				start++;
		}
		i++;
	}
	if (start < i)
		create_or_update_buffer(&buffer, str, start, i);
	create_or_update_lst(unit, buffer);
	return (end + 1);
}

int	handle_single_quote(char *str, int i, t_pipe_unit *unit)
{
	int		end;
	char	*substr;

	i++;
	end = check_quote_sanity(str, i, '\'');
	if (end == -1) // error message to add
		return (-1);
	substr = ft_substr(str, i, end - i);
    create_or_update_lst(unit, substr);
	end += 1;
	return (end);
}

int	handle_quote(char *str, int i, t_env *env, t_pipe_unit *unit)
{
	(void)str;
	(void)i;

	if (str[i] == '\"')
	{
		i = handle_double_quote(str, i + 1, env, unit);
	}
	else
		i = handle_single_quote(str, i, unit);
	if (i == -1)
		return (-1);
	return (i);
}