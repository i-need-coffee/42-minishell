#include "minishell.h"

static void	run_child_process(t_mini *mini, int i);
static int	pipe_and_fork(t_mini *mini, int i);

/*
**	Forks one child process per command in the pipeline, running each
**	in run_child_process; closes the parent's copies of all fds.
*/
int	create_children(t_mini *mini)
{
	int	i;

	mini->pids = malloc(mini->cmd_nb * sizeof(pid_t));
	if (!mini->pids)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	i = 0;
	while (i < mini->cmd_nb)
	{
		if (!pipe_and_fork(mini, i))
			return (0);
		i++;
	}
	close_all_fds(mini);
	return (1);
}

/*
**	Waits for every forked child and stores the last one's exit status
**	(or 128 + signal number if it was killed) in mini->err_num.
*/
void	wait_children(t_mini *mini)
{
	int		status;
	int		i;

	i = 0;
	while (i < mini->cmd_nb)
	{
		while (waitpid(mini->pids[i], &status, 0) == -1)
		{
			if (errno != EINTR)
				return (perror(ERR_WAITPID));
		}
		i++;
	}
	if (WIFEXITED(status))
		mini->err_num = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		mini->err_num = 128 + WTERMSIG(status);
}

/*
**	Creates the pipe for command i (if needed) and forks it, running
**	run_child_process in the child; keeps only the read end for the
**	next command and closes fds no longer needed in the parent.
*/
static int	pipe_and_fork(t_mini *mini, int i)
{
	if (mini->pipe_nb && pipe(mini->fds) == -1)
	{
		mini->err_num = 1;
		return (perror(ERR_PIPE), 0);
	}
	mini->pids[i] = fork();
	if (mini->pids[i] == -1)
	{
		mini->err_num = 1;
		return (perror(ERR_FORK), 0);
	}
	if (mini->pids[i] == 0)
		run_child_process(mini, i);
	safe_close(&mini->old_rd_fd);
	mini->old_rd_fd = mini->fds[0];
	safe_close(&mini->fds[1]);
	return (1);
}

/*
**	Sets up a child's redirections/pipes/fds, then runs its command:
**	a built-in directly, or an external command via execute_cmd.
*/
static void	run_child_process(t_mini *mini, int i)
{
	t_pipe_unit	*cmd;
	int			exec_error;

	signal(SIGQUIT, SIG_DFL);
	if (!open_files(mini->units, i))
		cleanup_exit(mini, 1);
	if (mini->pipe_nb && !dup_pipes(mini, i))
		cleanup_exit(mini, 1);
	if (!dup_redirects(mini->units, i))
		cleanup_exit(mini, 1);
	close_all_fds(mini);
	cmd = get_cmd_unit(mini->units, i);
	if (!cmd)
		cleanup_exit(mini, 0);
	if (!is_cmd_empty(cmd) && is_built_in(cmd))
	{
		exec_error = execute_built_in(mini, cmd);
		cleanup_exit(mini, exec_error);
	}
	exec_error = execute_cmd(mini, cmd);
	if (exec_error != 0)
		cleanup_exit(mini, exec_error);
}
