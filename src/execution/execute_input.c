/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:10:41 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/31 20:26:22 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_exec_data(t_mini *mini);
static char	**build_envp_tab(t_env *env);
static int	exec_in_parent(t_mini *mini, t_pipe_unit *cmd);

/*
**	Runs the parsed pipeline: sets up heredocs and pipes, then either
**	executes a single built-in in the parent or forks children.
*/
void	execute_input(t_mini *mini)
{
	t_pipe_unit	*cmd;

	init_exec_data(mini);
	mini->err_num = execute_heredocs(mini);
	if (mini->err_num != 0)
		return ;
	init_signal_child();
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
**	Builds a NULL-terminated "KEY=value" string array from the env
**	linked list, suitable for passing to execve().
*/
static char	**build_envp_tab(t_env *env)
{
	char	**envp;
	char	*temp;
	int		i;
	int		env_nodes;

	env_nodes = count_env_nodes(env);
	envp = malloc((env_nodes + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		if (!temp)
			return (free_char_tab(envp), NULL);
		envp[i] = ft_strjoin(temp, env->value);
		free(temp);
		if (!envp[i])
			return (free_char_tab(envp), NULL);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
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
