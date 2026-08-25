/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:11:04 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/25 17:11:05 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_errors(t_mini *mini, char **args);
static int	is_numeric_arg(char *arg);

/*
**	Exits the shell with args[1] % 256 as status (or 0 if no arg),
**	printing "exit" first unless inside a pipeline. If args[1] fails
**	numeric validation, exits directly from check_errors; if there are
**	too many arguments, prints an error and returns 1 without exiting.
*/
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

/*
**	Validates args[1] as a numeric exit code and checks for excess
**	arguments, printing errors and exiting/returning as appropriate.
*/
static int	check_errors(t_mini *mini, char **args)
{
	if (!is_numeric_arg(args[1]))
	{
		if (mini->pipe_nb == 0)
			printf("exit\n");
		print_error3(ERR_EXIT, args[1], ERR_EXIT_NUM);
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

/*
**	Returns 1 if arg is all zeros or converts to a non-zero long long
**	via ft_str_to_lld, 0 if the conversion yields 0 (i.e. arg is not
**	numeric).
*/
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
