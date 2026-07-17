#include "minishell.h"

static void	set_data(int *has_newline, int *i, int *last_arg, char **args);
static int	is_n_flag(char *arg);
static int	count_args(char **args);

int	echo(char **args)
{
	int	has_newline;
	int	i;
	int	last_arg;

	set_data(&has_newline, &i, &last_arg, args);
	while (args[i] && is_n_flag(args[i]))
		i++;
	while (args[i])
	{
		if (write(STDOUT_FILENO, args[i], ft_strlen(args[i])) == -1)
			return (perror(ERR_WRITE), 0);
		if (i != last_arg)
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
				return (perror(ERR_WRITE), 0);
		}
		i++;
	}
	if (has_newline)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (perror(ERR_WRITE), 0);
	}
	return (1);
}

static void	set_data(int *has_newline, int *i, int *last_arg, char **args)
{
	*has_newline = 1;
	*i = 1;
	if (args[1] && is_n_flag(args[1]))
	{
		*has_newline = 0;
		*i = 2;
	}
	*last_arg = count_args(args) - 1;
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
