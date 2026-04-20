#include "minishell.h"

static size_t	get_token_length(char *input);

void	add_word_token(t_mini *mini, int *i)
{
	char	*value;
	size_t	len;
	int		expand;

	expand = 0;
	if (mini->input[*i] == '"')
		expand = 1;
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
	if (!add_token(&mini->tokens, TOKEN_WORD, value, expand))
	{
		free(value);
		cleanup_exit(mini, EXIT_FAILURE);
	}
	free(value);
	(*i) += len;
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
