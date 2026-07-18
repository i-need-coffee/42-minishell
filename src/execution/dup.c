#include "minishell.h"

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

void	restore_fds(t_mini *mini, int saved_stdin, int saved_stdout)
{
	while (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		if (errno != EINTR)
			break;
	}
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		safe_close(&saved_stdin);
		safe_close(&saved_stdout);
		print_error_and_exit(mini, ERR_RESTORE_FDS, EXIT_FAILURE);
	}
	safe_close(&saved_stdin);
	while (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		if (errno != EINTR)
			break;
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		safe_close(&saved_stdout);
		print_error_and_exit(mini, ERR_RESTORE_FDS, EXIT_FAILURE);
	}
	safe_close(&saved_stdout);
}
