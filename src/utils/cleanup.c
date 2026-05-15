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
