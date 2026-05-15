#include "minishell.h"

static int	get_substr_len(char *input);
static char	*get_token_value(char *substr, char quotes_type);
static int	get_token_length(char *substr, char quotes_type);

void	add_word_token(t_mini *mini, int *i)
{
	int		len;
	char	*substr;
	char	quotes_type;
	char	*value;
	int		expands;

	len = get_substr_len(mini->input + *i);
	substr = ft_substr(mini->input, *i, len);
	if (!substr)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	quotes_type = substr[0];
	value = get_token_value(substr, quotes_type);
	free(substr);
	if (!value)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	expands = 0;
	if (has_env_variable(value) && quotes_type != '\'')
		expands = 1;
	if (!add_token(&mini->tokens, TOKEN_WORD, value, expands))
	{
		free(value);
		cleanup_exit(mini, EXIT_FAILURE);
	}
	free(value);
	(*i) += len;
}

static int	get_substr_len(char *input)
{
	int	len;
	int	in_s_quotes;
	int	in_d_quotes;

	len = 0;
	in_s_quotes = 0;
	in_d_quotes = 0;
	while (input[len])
	{
		if (input[len] == '\'' && !in_d_quotes)
			in_s_quotes = !in_s_quotes;
		if (input[len] == '"' && !in_s_quotes)
			in_d_quotes = !in_d_quotes;
		if ((ft_isspace(input[len]) && !in_s_quotes && !in_d_quotes))
			break ;
		len++;
	}
	return (len);
}

static char	*get_token_value(char *substr, char quotes_type)
{
	char	*value;
	int		i;
	int		j;
	int		len;

	if (quotes_type != '\'' && quotes_type != '"')
		return (ft_strdup(substr));
	len = get_token_length(substr, quotes_type);
	value = malloc((len + 1) * sizeof(char));
	if (!value)
		return (NULL);
	i = 0;
	j = 0;
	while (substr[i])
	{
		if (substr[i] != quotes_type)
		{
			value[j] = substr[i];
			j++;
		}
		i++;
	}
	value[j] = '\0';
	return (value);
}

static int	get_token_length(char *substr, char quotes_type)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (substr[i])
	{
		if (substr[i] != quotes_type)
			len++;
		i++;
	}
	return (len);
}
