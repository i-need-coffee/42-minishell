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

int	dup_saved_fds(int stdin, int stdout)
{
	if (dup2(STDIN_FILENO, stdin) == -1)
		return (perror(ERR_DUP2), 0);
	if (dup2(STDOUT_FILENO, stdout) == -1)
		return (perror(ERR_DUP2), 0);
	return (1);
}
