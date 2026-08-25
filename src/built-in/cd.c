/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:10:54 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/25 17:10:56 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Changes the current working directory to args[1], or $HOME if no
**	argument is given.
*/
int	cd(t_env *env, char **args)
{
	int		arg_count;
	char	*path;

	arg_count = count_args(args);
	if (arg_count > 2)
		return (print_error(ERR_CD_ARGS_NUM), 1);
	else if (arg_count == 1 || ft_strcmp(args[1], "~") == 0)
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
		return (print_error3(ERR_CD, path, strerror(errno)), 1);
	return (0);
}
