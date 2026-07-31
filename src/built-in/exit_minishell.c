#include "minishell.h"

void	exit_minishell(t_mini *mini, char **args)
{
	int	exit_code;

	exit_code = 0;
	(void)args;
	if (mini->pipe_nb == 0)
		printf("exit\n");
	cleanup_exit(mini, exit_code);
}
