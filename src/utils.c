#include "minishell.h"

void	cleanup(t_mini *mini)
{
	if (mini->tokens)
		free_tokens(&mini->tokens);
	if (mini->input)
		free(mini->input);
}

void	cleanup_exit(t_mini *mini, int exit_code)
{
	cleanup(mini);
	exit(exit_code);
}

int	has_unclosed_quotes(char *input)
{
	int	i;
	int	in_s_quotes;
	int	in_d_quotes;

	i = 0;
	in_s_quotes = 0;
	in_d_quotes = 0;
	while(input[i])
	{
		if (input[i] == '\'' && !in_d_quotes)
			in_s_quotes = !in_s_quotes;
		if (input[i] == '"' && !in_s_quotes)
			in_d_quotes = !in_d_quotes;
		i++;
	}
	if (in_s_quotes || in_d_quotes)
		return (1);
	return (0);
}
