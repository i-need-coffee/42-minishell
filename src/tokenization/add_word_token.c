#include "minishell.h"

static int	get_token_length(char *input);

void	add_word_token(t_mini *mini, int *i)
{
	int		len;

	len = get_token_length(mini->input + *i);
	ft_printf("%d", len);
	cleanup_exit(mini, EXIT_SUCCESS);
}

static int	get_token_length(char *input)
{
	int	i;
	int	len;
	int	in_s_quotes;
	int	in_d_quotes;

	i = 0;
	len = 0;
	in_s_quotes = 0;
	in_d_quotes = 0;
	while(input[i])
	{
		if (input[i] == '\'' && !in_d_quotes)
			in_s_quotes = !in_s_quotes;
		if (input[i] == '"' && !in_s_quotes)
			in_d_quotes = !in_d_quotes;
		if (ft_isspace(input[i]) && !in_s_quotes && !in_d_quotes)
			break ;
		if (! ((input[i] == '\'' && !in_d_quotes) || (input[i] == '"' && !in_s_quotes)))
			len++;
		i++;
	}
	return (len);
}

/* void	add_word_token(t_mini *mini, int *i)
{
	char		*value;
	size_t		len;

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
	if (!add_token(&mini->tokens, TOKEN_WORD, value))
	{
		free(value);
		cleanup_exit(mini, EXIT_FAILURE);
	}
	free(value);
	(*i) += len;
}
*/
