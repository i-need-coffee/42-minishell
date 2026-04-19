#include "minishell.h"

void	free_minishell(t_mini *mini)
{
	if (mini->tokens)
		free_tokens(&mini->tokens);
	if (mini->input)
		free(mini->input);
}
