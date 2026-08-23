#include "minishell.h"

static void	init_exec_data(t_mini *mini);
static int	exec_in_parent(t_mini *mini, t_pipe_unit *cmd);

/*
**	Runs the parsed pipeline: sets up heredocs and pipes, then either
**	executes a single built-in in the parent or forks children.
*/
void	execute_input(t_mini *mini)
{
	t_pipe_unit	*cmd;

	init_exec_data(mini);
	if (!execute_heredocs(mini))
	{
		mini->err_num = 1;
		return ;
	}
	init_signal_child();
	if (mini->pipe_nb && !create_pipes(mini))
		return ;
	cmd = get_cmd_unit(mini->units, 0);
	if (mini->cmd_nb == 1 && is_cmd_empty(cmd))
	{
		mini->err_num = 0;
		return ;
	}
	if (mini->cmd_nb == 1 && !is_cmd_empty(cmd) && is_built_in(cmd))
	{
		mini->err_num = exec_in_parent(mini, cmd);
		return ;
	}
	if (!create_children(mini))
		return ;
	wait_children(mini);
}

/*
**	Counts pipes to derive cmd_nb, and builds the envp array used by
**	execve() for this run.
*/
static void	init_exec_data(t_mini *mini)
{
	t_pipe_unit	*unit;

	unit = mini->units;
	while (unit)
	{
		if (unit->type == PIPE_OUT)
			mini->pipe_nb++;
		unit = unit->next;
	}
	mini->cmd_nb = mini->pipe_nb + 1;
	mini->envp = build_envp_tab(mini->env);
	if (!mini->envp)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
}

/*
**	Runs a lone built-in in the parent shell (so state like cd/export
**	persists) with fds redirected, then restores the original fds.
*/
static int	exec_in_parent(t_mini *mini, t_pipe_unit *cmd)
{
	int	exec_result;

	if (!open_files(mini->units, 0))
		return (1);
	if (!dup_saved_fds(&mini->saved_stdin, &mini->saved_stdout))
		return (1);
	if (!dup_redirects(mini->units, 0))
		return (1);
	exec_result = execute_built_in(mini, cmd);
	return (exec_result);
}
