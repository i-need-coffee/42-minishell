#include "minishell.h"

/*
**	Frees per-iteration data. Called after each readline iteration.
*/
void	cleanup(t_mini *mini)
{
	if (mini->tokens)
		free_tokens(&mini->tokens);
	if (mini->input)
		free(mini->input);
	if (mini->units)
		free_pipe_units(&mini->units);
	if (mini->pipes)
		free_and_close_pipes(mini);
}

/*
**	Frees everything and exits with the given exit code.
*/
void	cleanup_exit(t_mini *mini, int exit_code)
{
	free_everthing(mini);
	exit(exit_code);
}

/*
**	Frees all resources owned by the mini struct.
**	Should only be used in case of program error (eg. malloc failure)
**	or at the end of the program.
*/
void	free_everthing(t_mini *mini)
{
	cleanup(mini);
	free_env(&mini->env);
}
