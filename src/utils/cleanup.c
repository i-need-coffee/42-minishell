#include "minishell.h"

void	free_env_vars(t_env **root)
{
	t_env	*curr;
	t_env	*temp;

	curr = *root;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	*root = NULL;
}

/*
**	Frees per-iteration data and restores the saved stdin/stdout fds.
**	Called after each readline iteration; if restoring the fds fails,
**	prints an error, frees env, and exits immediately.
*/
void	cleanup(t_mini *mini)
{
	mini->pipe_nb = 0;
	mini->cmd_nb = 0;
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
	free_env_vars(&mini->env);
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
