/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:10:54 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/31 19:37:33 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env_pwd(t_env *env, char *prev_dir);

/*
**	Changes the current working directory to args[1], or $HOME if no
**	argument is given.
*/
int	cd(t_env *env, char **args)
{
	int		arg_count;
	char	*path;
	char	*curr_dir;

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
	curr_dir = get_curr_dir();
	if (!curr_dir)
		return (print_error(ERR_ALLOC_CD), 1);
	if (chdir(path) == -1)
		return (print_error3(ERR_CD, path, strerror(errno)), 1);
	if (!update_env_pwd(env, curr_dir))
		return (1);
	return (0);
}

/*
**	Updates OLDPWD with prev_dir and PWD with the new current directory.
*/
static int	update_env_pwd(t_env *env, char *prev_dir)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*new_curr_dir;

	old_pwd = get_env_node_with_key(&env, "OLDPWD");
	if (old_pwd)
	{
		free_and_null(&old_pwd->value);
		old_pwd->value = prev_dir;
	}
	else
		free(prev_dir);
	pwd = get_env_node_with_key(&env, "PWD");
	if (pwd)
	{
		new_curr_dir = get_curr_dir();
		if (!new_curr_dir)
			return (print_error(ERR_ALLOC_CD), 0);
		free_and_null(&pwd->value);
		pwd->value = new_curr_dir;
	}
	return (1);
}
