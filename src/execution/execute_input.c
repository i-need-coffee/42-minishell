#include "minishell.h"

static int	exec_in_parent(t_mini *mini, t_pipe_unit *cmd);

void	init_data(t_mini *mini)
{
	t_pipe_unit	*u1;

	// unset USER
	u1 = calloc(1, sizeof(t_pipe_unit));
	u1->type = CMD;
	u1->args = malloc(sizeof(char *) * 3);
	u1->args[0] = ft_strdup("export");
	u1->args[1] = ft_strdup("NEWKEY=NEWVALUE=NEWVALUE2");
	u1->args[2] = NULL;
	u1->fd = -1;
	u1->cmd_index = 0;
	u1->next = NULL;

	mini->units = u1;
	mini->pipe_nb = 0;
}

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

void	execute_input(t_mini *mini)
{
	t_pipe_unit	*cmd;

	init_data(mini);
	mini->cmd_nb = mini->pipe_nb + 1;
	mini->envp = build_envp_tab(mini->env);
	if (!mini->envp)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
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
