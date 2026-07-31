#include "minishell.h"

static int	check_errors(t_mini *mini, char **args);
static int	is_numeric_arg(char *arg);

int	exit_minishell(t_mini *mini, char **args)
{
	int			i;
	long long	nb;

	if (count_args(args) > 1)
	{
		if (!check_errors(mini, args))
			return (1);
		i = 0;
		while (args[1][i] && args[1][i] == '0')
			i++;
		if (i == (int)ft_strlen(args[1]))
		{
			if (mini->pipe_nb == 0)
				printf("exit\n");
			cleanup_exit(mini, 0);
		}
		nb = ft_str_to_lld(args[1]);
		if (mini->pipe_nb == 0)
			printf("exit\n");
		cleanup_exit(mini, nb % 256);
	}
	if (mini->pipe_nb == 0)
		printf("exit\n");
	cleanup_exit(mini, 0);
	return (0);
}

static int	check_errors(t_mini *mini, char **args)
{
	if (!is_numeric_arg(args[1]))
	{
		if (mini->pipe_nb == 0)
			printf("exit\n");
		ft_putstr_fd(ERR_EXIT, 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(ERR_EXIT_NUM, 2);
		ft_putstr_fd("\n", 2);
		cleanup_exit(mini, 2);
	}
	if (count_args(args) > 2)
	{
		if (mini->pipe_nb == 0)
			printf("exit\n");
		print_error(ERR_EXIT_ARGS_NUM);
		return (0);
	}
	return (1);
}

static int	is_numeric_arg(char *arg)
{
	long long	nb;
	int			i;

	i = 0;
	while (arg[i] && arg[i] == '0')
		i++;
	if (i == (int)ft_strlen(arg))
		return (1);
	nb = ft_str_to_lld(arg);
	if (nb == 0)
		return (0);
	return (1);
}
