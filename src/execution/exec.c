#include "minishell.h"

static char	*get_cmd_path(char *env_path, char *cmd);
static int	print_exec_error(char *cmd, int error);

/*
**	Executes an external command: runs it directly if it contains a
**	'/' or PATH is unusable, otherwise resolves it through PATH first.
*/
int	execute_cmd(t_mini *mini, t_pipe_unit *cmd)
{
	char	*env_path;
	char	*cmd_path;
	int		exit_code;

	if (is_cmd_empty(cmd))
		cleanup_exit(mini, 0);
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

/*
**	Searches each directory in env_path for an executable named
**	cmd_arg and returns its full path, or NULL if none is found.
*/
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

/*
**	Prints the appropriate error message for a failed execve() and
**	returns the matching shell exit code (127 or 126).
*/
static int	print_exec_error(char *cmd, int error)
{
	if (error == ENOENT && !ft_strchr(cmd, '/'))
		print_error3("minishell", cmd, ERR_CMD_NOT_FOUND);
	else if (error == EACCES && cmd[0] == '/')
		print_error3("minishell", cmd, ERR_IS_A_DIR);
	else
		print_error3("minishell", cmd, strerror(error));
	if (error == ENOENT)
		return (127);
	else
		return (126);
}
