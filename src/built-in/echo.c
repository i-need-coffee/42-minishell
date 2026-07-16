#include "minishell.h"

void	echo(char **args)
{
	int	has_newline;
	int	i;

	has_newline = 1;
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		has_newline = 0;
		i = 2;
	}
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
	}
	if (has_newline)
		write(STDOUT_FILENO, "\n", 1);
}
