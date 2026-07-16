#include "minishell.h"

int	is_built_in(t_pipe_unit *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	return (0);
}

void	execute_built_in(t_pipe_unit *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		echo(cmd->args);
}
