#include "minishell.h"

int	cd(char **args)
{
	if (count_args(args) > 2)
		return (print_error(ERR_CD_ARGS_NUM), 1);
	return (0);
}
