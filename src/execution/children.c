#include "minishell.h"

static void	run_child_process(t_mini *mini, int i);

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
		{
			mini->err_num = 1;
			return (perror(ERR_FORK), 0);
		}
		if (mini->pids[i] == 0)
			run_child_process(mini, i);
		i++;
	}
	close_all_fds(mini->units);
	return (1);
}
void	wait_children(t_mini *mini)
{
	int		status;
	int		i;

	i = 0;
	while (i < mini->cmd_nb)
	{
		if (waitpid(mini->pids[i], &status, 0) == -1)
		{
			perror(ERR_WAITPID);
			return ;
		}
		i++;
	}
	if (WIFEXITED(status))
		mini->err_num = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		mini->err_num = 128 + WTERMSIG(status);
}

static void	run_child_process(t_mini *mini, int i)
{
	t_pipe_unit	*cmd;
	int			exec_error;

	if (!open_files(mini->units, i))
		cleanup_exit(mini, 1);
	if (mini->pipe_nb && !dup_pipes(mini->units, i))
		cleanup_exit(mini, 1);
	if (!dup_redirects(mini->units, i))
		cleanup_exit(mini, 1);
	close_all_fds(mini->units);
	cmd = get_cmd_unit(mini->units, i);
	if (!cmd)
		cleanup_exit(mini, 0);
	if (is_built_in(cmd))
	{
		exec_error = execute_built_in(mini, cmd);
		cleanup_exit(mini, exec_error);
	}
	exec_error = execute_cmd(mini, cmd);
	if (exec_error != 0)
		cleanup_exit(mini, exec_error);
}
