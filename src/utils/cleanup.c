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
	free_everthing(mini);
	exit(exit_code);
}

void	free_everthing(t_mini *mini)
{
	cleanup(mini);
	free_env(&mini->env);
}
