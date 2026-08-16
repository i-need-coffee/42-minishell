#include "minishell.h"

int	increment(int *start, int *i, int *end)
{
	*start = *i;
	if (*i == *end)
		(*start)++;
	return (1);
}

int	dup_and_free(char **b, char **quote_buffer)
{
	if (!*quote_buffer)
		return (0);
	*b = ft_strdup(*quote_buffer);
	free_and_null(quote_buffer);
	return (0);
}

int	handle_double_quote(char *str, int i, t_mini *mini, char **b)
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
		if ((str[i] == '$' && str[i + 1] && ft_isalpha(str[i + 1]) && str[i
					+ 1] != '\"') || str[i + 1] == '_')
		{
			if ((create_or_update_buffer(&quote_buffer, str, start, i)) == 0)
				print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
			i = expension(str, i, mini, &quote_buffer);
			increment(&start, &i, &end);
		}
		i++;
	}
	if (!(wrapper_coub(&quote_buffer, str, start, i)))
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	dup_and_free(b, &quote_buffer);
	return (end + 1);
}

int	handle_single_quote(char *str, int i, char **b, t_mini *mini)
{
	int		end;
	char	*substr;

	i++;
	end = check_quote_sanity(str, i, '\'');
	if (end == 0)
		return (0);
	substr = ft_substr(str, i, end - i);
	if (!substr)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	*b = substr;
	end += 1;
	return (end);
}

int	handle_quote(char *str, int i, t_mini *mini, char **b)
{
	if (str[i] == '\"')
		i = handle_double_quote(str, i + 1, mini, b);
	else
		i = handle_single_quote(str, i, b, mini);
	if (i == 0)
		return (0);
	return (i);
}
