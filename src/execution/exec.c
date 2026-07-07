#include "minishell.h"

static t_pipe_unit	*get_cmd_unit(t_pipe_unit *units, int i);
static int			has_slash(char *cmd);
static char			*get_cmd_path(char *env_path, char *cmd);
static int			is_path_valid(char *path, char *cmd);

int	execute_cmd(t_mini *mini, int i)
{
	t_pipe_unit	*cmd;
	char		*env_path;
	char		*cmd_path;

	cmd = get_cmd_unit(mini->units, i);
	env_path = get_value_with_key(mini->env, "PATH");
	if (!env_path || !env_path[0] || has_slash(cmd->args[0]))
	{
		if (execve(cmd->args[0], cmd->args, mini->envp) == -1)
			return (print_perror(cmd->args[0], errno), 0);
	}
	cmd_path = get_cmd_path(env_path, cmd->args[0]);
	if (!cmd_path)
		return (perror(ERR_ALLOC), 0);
	if (!is_path_valid(cmd_path, cmd->args[0]))
		return (free(cmd_path), 0);
	if (execve(cmd_path, cmd->args, mini->envp) == -1)
		return (print_perror(cmd->args[0], errno), 0);
	return (1);
}

static t_pipe_unit	*get_cmd_unit(t_pipe_unit *units, int i)
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

static int	has_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_cmd_path(char *env_path, char *cmd_arg)
{
	char	*cmd_path;
	char	*cmd;
	char	**paths;
	int		i;

	cmd_path = NULL;
	cmd = ft_strjoin("/", cmd_arg);
	if (!cmd)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (free(cmd), NULL);
	i = 0;
	while (paths[i])
	{
		free_and_null(&cmd_path);
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
			return (free(cmd), free_char_tab(paths), NULL);
		if (access(cmd_path, F_OK) == 0)
			return (free(cmd), free_char_tab(paths), cmd_path);
		i++;
	}
	return (free(cmd), free_char_tab(paths), cmd_path);
}

static int	is_path_valid(char *path, char *cmd)
{
	if (access(path, F_OK) == -1)
	{
		write(2, "error: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Command not found", 19);
		write(2, "\n", 1);
		return (0);
	}
	if (access(path, X_OK) == -1)
	{
		write(2, "error: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Permission denied", 19);
		write(2, "\n", 1);
		return (0);
	}
	return (1);
}
