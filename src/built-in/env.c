#include "minishell.h"

int	env(char **envp, char **args)
{
	int		i;

	if (count_args(args) > 1)
		return (print_error(ERR_ENV_ARGS_NUM), 125);
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
