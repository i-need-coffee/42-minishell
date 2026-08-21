#include "minishell.h"

/*
**	Frees every pipe_unit in the list, closing its fd and releasing
**	its file/args, then nulls *root.
*/
void	free_pipe_units(t_pipe_unit **root)
{
	t_pipe_unit	*curr;
	t_pipe_unit	*temp;

	curr = *root;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		if (temp->file)
			free(temp->file);
		if (temp->args)
			free_char_tab(temp->args);
		safe_close(&temp->fd);
		free(temp);
	}
	*root = NULL;
}

/*
**	Closes every unit's fd across the whole pipeline and in the mini struct.
*/
void	close_all_fds(t_mini *mini)
{
	t_pipe_unit	*curr;

	curr = mini->units;
	while (curr)
	{
		safe_close(&curr->fd);
		curr = curr->next;
	}
	safe_close(&mini->fds[0]);
	safe_close(&mini->fds[1]);
	safe_close(&mini->old_rd_fd);
}

/*
**	Returns the CMD-type unit belonging to command index i, or NULL
**	if that command has none.
*/
t_pipe_unit	*get_cmd_unit(t_pipe_unit *units, int i)
{
	while (units && units->cmd_index != i)
		units = units->next;
	while (units && units->cmd_index == i)
	{
		if (units->type == CMD)
			return (units);
		units = units->next;
	}
	return (NULL);
}

/*
**	Builds a NULL-terminated "KEY=value" string array from the env
**	linked list, suitable for passing to execve().
*/
char	**build_envp_tab(t_env *env)
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
**	Check if cmd exists and if it has args.
*/
int	is_cmd_empty(t_pipe_unit *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0] || !cmd->args[0][0])
		return (1);
	return (0);
}
