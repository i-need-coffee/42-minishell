/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:11:08 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/29 17:32:07 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_node_to_env(t_env *env, char *arg);
static void	set_values(char *arg, char **key, char **value);
static int	is_key_valid(char *key);
static void	print_export_error(char *arg);

/*
**	With no args, prints all env vars in "declare -x" format; otherwise
**	adds/updates each KEY[=value] arg in env.
*/
int	export(t_env *env, char **args)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	if (count_args(args) == 1)
	{
		sort_env_nodes(&env);
		if (!print_env_nodes(&env))
			exit_code = 1;
		return (exit_code);
	}
	i = 1;
	while (args[i])
	{
		if (!add_node_to_env(env, args[i]))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}

/*
**	Parses arg into a key/value pair and either updates the matching
**	env node or appends a new one.
*/
static int	add_node_to_env(t_env *env, char *arg)
{
	char	*key;
	char	*value;
	t_env	*node;

	set_values(arg, &key, &value);
	if (!key || !value)
		return (free(key), free(value), print_error(ERR_ALLOC_EXPORT), 0);
	node = get_env_node_with_key(&env, key);
	if (node)
	{
		free(key);
		if (!ft_strchr(arg, '='))
			return (free(value), 1);
		free_and_null(&node->value);
		node->value = value;
		return (1);
	}
	if (!is_key_valid(key))
		return (print_export_error(arg), free(key), free(value), 0);
	node = new_node();
	if (!node)
		return (free(key), free(value), print_error(ERR_ALLOC_EXPORT), 0);
	node->key = key;
	node->value = value;
	return (add_back(&env, node), 1);
}

/*
**	Splits arg on '=' into freshly allocated *key and *value strings
**	(empty value if no '=' is present).
*/
static void	set_values(char *arg, char **key, char **value)
{
	int	key_len;
	int	value_len;

	if (!ft_strchr(arg, '='))
	{
		*key = ft_strdup(arg);
		*value = ft_strdup("\0");
		return ;
	}
	key_len = 0;
	while (arg[key_len] && arg[key_len] != '=')
		key_len++;
	*key = malloc((key_len + 1) * sizeof(char));
	if (!*key)
		return ;
	ft_strlcpy(*key, arg, key_len + 1);
	value_len = ft_strlen(arg) - key_len - 1;
	*value = malloc((value_len + 1) * sizeof(char));
	if (!*value)
		return ;
	ft_strlcpy(*value, arg + key_len + 1, value_len + 1);
}

/*
**	Returns 1 if key is a valid shell identifier (starts with a letter
**	or underscore, then alnum/underscore only).
*/
static int	is_key_valid(char *key)
{
	int	i;

	if (! (key[0] == '_' || ft_isalpha(key[0])))
		return (0);
	i = 0;
	while (key[i])
	{
		if (! (ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

/*
**	Prints the "not a valid identifier" error for a rejected export
**	argument.
*/
static void	print_export_error(char *arg)
{
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}
