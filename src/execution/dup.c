#include "minishell.h"

/*
**	Duplicates command i's pipe fds onto stdin/stdout (PIPE_IN/PIPE_OUT).
*/
int	dup_pipes(t_pipe_unit *units, int i)
{
	while (units && units->cmd_index != i)
		units = units->next;
	while (units && units->cmd_index == i)
	{
		if (units->type == PIPE_IN)
		{
			if (dup2(units->fd, STDIN_FILENO) == -1)
				return (perror(ERR_DUP2), 0);
		}
		if (units->type == PIPE_OUT)
		{
			if (dup2(units->fd, STDOUT_FILENO) == -1)
				return (perror(ERR_DUP2), 0);
		}
		units = units->next;
	}
	return (1);
}

/*
**	Duplicates command i's redirection fds onto stdin/stdout
**	(REDIR_IN/HEREDOC onto stdin, REDIR_OUT/APPEND onto stdout).
*/
int	dup_redirects(t_pipe_unit *units, int i)
{
	while (units && units->cmd_index != i)
		units = units->next;
	while (units && units->cmd_index == i)
	{
		if (units->type == REDIR_IN || units->type == HEREDOC)
		{
			if (dup2(units->fd, STDIN_FILENO) == -1)
				return (perror(ERR_DUP2), 0);
		}
		if (units->type == REDIR_OUT || units->type == APPEND)
		{
			if (dup2(units->fd, STDOUT_FILENO) == -1)
				return (perror(ERR_DUP2), 0);
		}
		units = units->next;
	}
	return (1);
}

/*
**	Saves the current stdin/stdout fds via dup() so they can be
**	restored later after temporary redirections.
*/
int	dup_saved_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
		return (perror(ERR_DUP), 0);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		perror(ERR_DUP);
		safe_close(saved_stdin);
		return (0);
	}
	return (1);
}

int	restore_saved_stdin(t_mini *mini)
{
	if (mini->saved_stdin == -1)
		return (1);
	while (dup2(mini->saved_stdin, STDIN_FILENO) == -1)
	{
		if (errno != EINTR)
			break ;
	}
	if (dup2(mini->saved_stdin, STDIN_FILENO) == -1)
	{
		safe_close(&mini->saved_stdin);
		return (0);
	}
	safe_close(&mini->saved_stdin);
	return (1);
}

int	restore_saved_stdout(t_mini *mini)
{
	if (mini->saved_stdout == -1)
		return (1);
	while (dup2(mini->saved_stdout, STDOUT_FILENO) == -1)
	{
		if (errno != EINTR)
			break ;
	}
	if (dup2(mini->saved_stdout, STDOUT_FILENO) == -1)
	{
		safe_close(&mini->saved_stdout);
		return (0);
	}
	safe_close(&mini->saved_stdout);
	return (1);
}
