#include "minishell.h"

/*
**	Counts the number of non-NULL entries in a NULL-terminated args
**	array.
*/
int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
