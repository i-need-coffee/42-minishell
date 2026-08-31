/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:10:54 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/29 20:55:53 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env_pwd(t_env *env);
static int	update_oldpwd(t_env *env, char *value);

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
	if (!update_env_pwd(env))
		return (1);
	return (0);
}

static int	update_env_pwd(t_env *env)
{
	t_env	*pwd;
	char	*curr_dir;

	curr_dir = get_curr_dir();
	if (!curr_dir)
		return (print_error(ERR_ALLOC_CD), 0);
	pwd = get_env_node_with_key(&env, "PWD");
	if (pwd)
	{
		if (!update_oldpwd(env, pwd->value))
			return (free(curr_dir), print_error(ERR_ALLOC_CD), 0);
		free_and_null(&pwd->value);
		pwd->value = curr_dir;
		return (1);
	}
	pwd = new_node();
	if (!pwd)
		return (free(curr_dir), print_error(ERR_ALLOC_CD), 0);
	pwd->key = ft_strdup("PWD");
	if (!pwd->key)
		return (free(curr_dir), free(pwd), print_error(ERR_ALLOC_CD), 0);
	pwd->value = curr_dir;
	return (add_back(&env, pwd), 1);
}

static int	update_oldpwd(t_env *env, char *value)
{
	t_env	*old_pwd;
	char	*new_value;

	new_value = ft_strdup(value);
	if (!new_value)
		return (print_error(ERR_ALLOC_CD), 0);
	old_pwd = get_env_node_with_key(&env, "OLDPWD");
	if (old_pwd)
	{
		free_and_null(&old_pwd->value);
		old_pwd->value = new_value;
		return (1);
	}
	old_pwd = new_node();
	if (!old_pwd)
		return (free(new_value), print_error(ERR_ALLOC_CD), 0);
	old_pwd->key = ft_strdup("OLDPWD");
	if (!old_pwd->key)
		return (free(new_value), free(old_pwd), print_error(ERR_ALLOC_CD), 0);
	old_pwd->value = new_value;
	return (add_back(&env, old_pwd), 1);
}
