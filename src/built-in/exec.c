#include "minishell.h"

int	is_built_in(t_pipe_unit *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	else
		return (0);
}

int	execute_built_in(t_pipe_unit *cmd)
{
	int	exec_result;

	exec_result = 0;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		exec_result = echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		exec_result = pwd();
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		exec_result = cd(cmd->args);
	return (exec_result);
}
