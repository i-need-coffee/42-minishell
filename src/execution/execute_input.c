#include "minishell.h"

static void	init_exec_data(t_mini *mini);
static int	exec_in_parent(t_mini *mini, t_pipe_unit *cmd);

void	print_data(t_mini *mini)
{
	t_pipe_unit	*curr;
	int			node;
	int			j;

	node = 0;
	curr = mini->units;
	while (curr)
	{
		ft_printf("── node[%d] ──────────────────────────────\n", node);
		ft_printf("  type     : %d\n", curr->type);
		ft_printf("  cmd_index: %d\n", curr->cmd_index);
		if (curr->args)
		{
			j = 0;
			while (curr->args[j])
			{
				ft_printf("  args[%d]  : %s\n", j, curr->args[j]);
				j++;
			}
		}
		if (curr->file)
			ft_printf("  file     : %s\n", curr->file);
		ft_printf("  fd       : %d\n", curr->fd);
		node++;
		curr = curr->next;
	}
	ft_printf("─────────────────────────────────────────\n");
}

/*
**	Runs the parsed pipeline: sets up heredocs and pipes, then either
**	executes a single built-in in the parent or forks children.
*/
void	execute_input(t_mini *mini)
{
	t_pipe_unit	*cmd;

	print_data(mini);
	init_exec_data(mini);
	printf("pipe nb: %d\n", mini->pipe_nb);
	printf("cmd nb: %d\n", mini->cmd_nb);
	if (!execute_heredocs(mini))
		return ;
	if (mini->pipe_nb && !create_pipes(mini))
		return ;
	cmd = get_cmd_unit(mini->units, 0);
	if (cmd && mini->cmd_nb == 1 && is_built_in(cmd))
	{
		mini->err_num = exec_in_parent(mini, cmd);
		return ;
	}
	if (!create_children(mini))
		return ;
	wait_children(mini);
}

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
	int	saved_stdin;
	int	saved_stdout;
	int	exec_result;

	saved_stdin = -1;
	saved_stdout = -1;
	if (!open_files(mini->units, 0))
		return (1);
	if (!dup_saved_fds(&saved_stdin, &saved_stdout))
		return (1);
	if (!dup_redirects(mini->units, 0))
		return (restore_fds(mini, saved_stdin, saved_stdout), 1);
	exec_result = execute_built_in(mini, cmd);
	restore_fds(mini, saved_stdin, saved_stdout);
	return (exec_result);
}
