#include "minishell.h"

static int	run_child_process(t_mini *mini);

int	create_children(t_mini *mini)
{
	int	i;
	int	num_cmds;

	num_cmds = mini->pipe_nb + 1;
	mini->pids = malloc(num_cmds * sizeof(pid_t));
	if (!mini->pids)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	i = 0;
	while (i < num_cmds)
	{
		mini->pids[i] = fork();
		if (mini->pids[i] == -1)
			return (perror(ERR_FORK), 0);
		if (mini->pids[i] == 0 && !run_child_process(mini, i))
			return (0);
		i++;
	}
	return (1);
}

static int	run_child_process(t_mini *mini, int i)
{
	while (mini->units)
	{

	}
	return (1);
}
