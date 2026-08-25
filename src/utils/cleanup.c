#include "minishell.h"

static void	set_mini_values_to_zero(t_mini *mini);

/*
**	Frees per-iteration data and restores the saved stdin/stdout fds.
**	Called after each readline iteration; if restoring the fds fails,
**	prints an error, frees env, and exits immediately.
*/
void	cleanup(t_mini *mini)
{
	set_mini_values_to_zero(mini);
	close_pipe_fds(mini);
	if (mini->tokens)
		free_tokens(&mini->tokens);
	if (mini->input)
		free(mini->input);
	if (mini->units)
		free_pipe_units(&mini->units);
	if (mini->pids)
	{
		free(mini->pids);
		mini->pids = NULL;
	}
	if (mini->envp)
	{
		free_char_tab(mini->envp);
		mini->envp = NULL;
	}
	if (!restore_saved_stdin(mini) || !restore_saved_stdout(mini))
	{
		print_error(ERR_RESTORE_FDS);
		free_env(&mini->env);
		exit(EXIT_FAILURE);
	}
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

/*
**	Set back some values to 0 in mini on each new line.
*/
static void	set_mini_values_to_zero(t_mini *mini)
{
	mini->pipe_nb = 0;
	mini->heredoc_filename = 0;
	mini->cmd_nb = 0;
}
