#include "minishell.h"

static int	is_n_flag(char *arg);
static int	count_args(char **args);

void	echo(char **args)
{
	int	has_newline;
	int	i;
	int	last_arg;

	has_newline = 1;
	i = 1;
	if (args[1] && is_n_flag(args[1]))
	{
		has_newline = 0;
		i = 2;
	}
	while (args[i] && is_n_flag(args[i]))
		i++;
	last_arg = count_args(args) - 1;
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (i != last_arg)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (has_newline)
		write(STDOUT_FILENO, "\n", 1);
}

static int	is_n_flag(char *arg)
{
	int	i;

	if (ft_strlen(arg) < 2)
		return (0);
	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
