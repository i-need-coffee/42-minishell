#include "minishell.h"

void	add_word_token(t_mini *mini, int *i)
{
	int		j;
	size_t	len;
	char	*value;

	j = *i;
	len = 0;
	while (mini->input[j] && !ft_isspace(mini->input[j]))
	{
		len++;
		j++;
	}
	value = ft_substr(mini->input, *i, len);
	if (!value)
	{
		perror("minishell");
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
