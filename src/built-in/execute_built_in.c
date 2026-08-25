/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:11:01 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/25 17:11:03 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Returns 1 if cmd's command name matches one of the supported
**	built-ins, 0 otherwise.
*/
int	is_built_in(t_pipe_unit *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	else
		return (0);
}

/*
**	Dispatches cmd to the matching built-in function and returns its
**	exit status.
*/
int	execute_built_in(t_mini *mini, t_pipe_unit *cmd)
{
	int	exec_result;

	exec_result = 0;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		exec_result = echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		exec_result = pwd();
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		exec_result = cd(mini->env, cmd->args);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		exec_result = env(mini->envp, cmd->args);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		exec_result = unset(&mini->env, cmd->args);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		exec_result = export(mini->env, cmd->args);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exec_result = exit_minishell(mini, cmd->args);
	return (exec_result);
}
