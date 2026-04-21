#include "minishell.h"

static t_quotes	get_quotes_type(char *input);
static size_t	get_token_length(char *input);

void	add_word_token(t_mini *mini, int *i)
{
	char		*value;
	size_t		len;
	t_quotes	quotes;

	quotes = get_quotes_type(mini->input + *i);
	len = get_token_length(mini->input + *i);
	if (mini->input[*i] == '\'' || mini->input[*i] == '"')
		value = ft_substr(mini->input, *i + 1, len - 2);
	else
		value = ft_substr(mini->input, *i, len);
	if (!value)
	{
		perror("error");
		cleanup_exit(mini, EXIT_FAILURE);
	}
	if (!add_token(&mini->tokens, TOKEN_WORD, quotes, value))
	{
		free(value);
		cleanup_exit(mini, EXIT_FAILURE);
	}
	free(value);
	(*i) += len;
}

static t_quotes	get_quotes_type(char *input)
{
	t_quotes	quotes;

	if (input[0] == '\'')
		quotes = SINGLE_QUOTES;
	else if (input[0] == '"')
		quotes = DOUBLE_QUOTES;
	else
		quotes = NO_QUOTES;
	return (quotes);
}

static size_t	get_token_length(char *input)
{
	size_t	i;

	i = 0;
	if (input[0] == '"')
	{
		i++;
		while (input[i] && input[i] != '"')
			i++;
		if (input[i] == '"')
			i++;
	}
	else if (input[0] == '\'')
	{
		i++;
		while (input[i] && input[i] != '\'')
			i++;
		if (input[i] == '\'')
			i++;
	}
	else
	{
		while (input[i] && !ft_isspace(input[i]))
			i++;
	}
	return (i);
}
