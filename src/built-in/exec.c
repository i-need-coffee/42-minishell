#include "minishell.h"

int	is_built_in(t_pipe_unit *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	return (0);
}

int	execute_built_in(t_pipe_unit *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
	{
		if (!echo(cmd->args))
			return (1);
	}
	return (0);
}
