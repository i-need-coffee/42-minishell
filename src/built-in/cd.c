#include "minishell.h"

int	cd(t_env *env, char **args)
{
	int		arg_count;
	char	*path;

	arg_count = count_args(args);
	if (arg_count > 2)
		return (print_error(ERR_CD_ARGS_NUM), 1);
	else if (arg_count == 1)
	{
		path = get_value_with_key(env, "HOME");
		if (!path)
			return (print_error(ERR_CD_NO_HOME), 1);
		if (!path[0])
			return (0);
	}
	else
		path = args[1];
	if (chdir(path) == -1)
		return (perror(ERR_CD), 1);
	return (0);
}
