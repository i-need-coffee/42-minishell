#include "minishell.h"

/*
**	Prints every "KEY=value" entry of envp; fails if called with any
**	arguments.
*/
int	env(char **envp, char **args)
{
	int		i;

	if (count_args(args) > 1)
		return (print_error(ERR_ENV_ARGS_NUM), 1);
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
