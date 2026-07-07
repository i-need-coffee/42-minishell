#include "minishell.h"

static t_pipe_unit	*get_cmd_unit(t_pipe_unit *units, int i);
static char			*get_cmd_path(char *env_path, char *cmd);
static int			print_exec_error(char *cmd, int error);

int	execute_cmd(t_mini *mini, int i)
{
	t_pipe_unit	*cmd;
	char		*env_path;
	char		*cmd_path;
	int			exit_code;

	cmd = get_cmd_unit(mini->units, i);
	env_path = get_value_with_key(mini->env, "PATH");
	if (!env_path || !env_path[0] || ft_strchr(cmd->args[0], '/'))
	{
		if (execve(cmd->args[0], cmd->args, mini->envp) == -1)
		{
			exit_code = print_exec_error(cmd->args[0], errno);
			return (exit_code);
		}
	}
	cmd_path = get_cmd_path(env_path, cmd->args[0]);
	if (!cmd_path)
		return (perror(ERR_ALLOC), 1);
	if (execve(cmd_path, cmd->args, mini->envp) == -1)
	{
		free(cmd_path);
		exit_code = print_exec_error(cmd->args[0], errno);
		return (exit_code);
	}
	return (0);
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

static int	print_exec_error(char *cmd, int error)
{
	if (error == ENOENT && !ft_strchr(cmd, '/'))
	{
		write(2, "error: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Command not found\n", 20);
	}
	else if (error == EACCES && cmd[0] == '/')
	{
		write(2, "error: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Is a directory\n", 17);
	}
	else
		print_perror(cmd, error);
	if (error == ENOENT)
		return (127);
	else
		return (126);
}
