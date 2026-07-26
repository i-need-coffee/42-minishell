#include "minishell.h"

static void	set_data(int *has_newline, int *i, int *last_arg, char **args);
static int	is_n_flag(char *arg);

/*
**	Writes args to stdout, space-separated, honoring a leading -n flag
**	to suppress the trailing newline.
*/
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
			return (perror(ERR_ECHO), 1);
		if (i != last_arg)
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
				return (perror(ERR_ECHO), 1);
		}
		i++;
	}
	if (has_newline)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (perror(ERR_ECHO), 1);
	}
	return (0);
}

/*
**	Detects a leading -n flag and computes the starting index and
**	index of the last argument.
*/
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

/*
**	Returns 1 if arg is a valid -n flag (e.g. "-n", "-nnn"), 0
**	otherwise.
*/
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
