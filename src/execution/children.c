#include "minishell.h"

static void	run_child_process(t_mini *mini, int i);
static int	dup_pipes(t_pipe_unit *units, int i);
static int	dup_redirects(t_pipe_unit *units, int i);

int	create_children(t_mini *mini)
{
	int	i;

	mini->pids = malloc(mini->cmd_nb * sizeof(pid_t));
	if (!mini->pids)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	i = 0;
	while (i < mini->cmd_nb)
	{
		mini->pids[i] = fork();
		if (mini->pids[i] == -1)
			return (perror(ERR_FORK), 0);
		if (mini->pids[i] == 0)
			run_child_process(mini, i);
		i++;
	}
	return (1);
}

static void	run_child_process(t_mini *mini, int i)
{
	if (!open_files(mini->units, i))
		cleanup_exit(mini, 1);
	if (mini->pipe_nb && !dup_pipes(mini->units, i))
		cleanup_exit(mini, 1);
	if (!dup_redirects(mini->units, i))
		cleanup_exit(mini, 1);
}

static int	dup_pipes(t_pipe_unit *units, int i)
{
	while (units)
	{
		if (units->cmd_index == i)
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
		}
		units = units->next;
	}
	return (1);
}

static int	dup_redirects(t_pipe_unit *units, int i)
{
	while (units)
	{
		if (units->cmd_index == i)
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
		}
		units = units->next;
	}
	return (1);
}
