#include "minishell.h"

int	execute_built_in(t_mini *mini, int i)
{
	t_pipe_unit	*cmd;

	cmd = get_cmd_unit(mini->units, i);
	if (!cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
	{
		ft_echo(cmd->args);
		return (1);
	}
	return (0);
}
