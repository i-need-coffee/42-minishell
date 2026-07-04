#include "minishell.h"

void	execute_cmd(t_mini *mini)
{
	char	*env_path;

	//TODO: do execve using the cmd as the path in case env_path is NULL
	env_path = get_value_with_key(mini->env, "PATH");
	if (env_path)
		ft_printf("%s\n", env_path);
}
