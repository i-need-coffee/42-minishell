#include "minishell.h"

int	cd(char **args)
{
	int	arg_count;

	arg_count = count_args(args);
	if (arg_count > 2)
		return (print_error(ERR_CD_ARGS_NUM), 1);
	return (0);
}
