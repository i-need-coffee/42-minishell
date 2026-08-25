/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:10:59 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/25 17:11:00 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Prints every "KEY=value" entry of envp; fails if called with any
**	arguments.
*/
int	env(char **envp, char **args)
{
	int		i;

	if (count_args(args) > 1)
		return (print_error(ERR_ENV_ARGS_NUM), 1);
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
