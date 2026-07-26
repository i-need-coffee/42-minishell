#include "minishell.h"

static int	add_node_to_env(t_mini *mini, char *arg);
static void	set_values(char *arg, char **key, char **value);
static int	is_key_valid(char *key);
static void	print_export_error(char *arg);

int	export(t_mini *mini, char **args)
{
	int		i;

	if (count_args(args) == 1)
	{
		sort_env_nodes(&mini->env);
		print_env_nodes(mini);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!add_node_to_env(mini, args[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	add_node_to_env(t_mini *mini, char *arg)
{
	char	*key;
	char	*value;
	t_env	*node;

	set_values(arg, &key, &value);
	if (!key || !value)
		return (free(key), free(value), print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE), 0);
	node = get_env_node_with_key(&mini->env, key);
	if (node)
	{
		free_and_null(&node->value);
		node->value = value;
		free(key);
		return (1);
	}
	if (!is_key_valid(key))
		return (print_export_error(arg), free(key), free(value), 0);
	node = new_node();
	if (!node)
		return (free(key), free(value), print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE), 0);
	node->key = key;
	node->value = value;
	add_back(&mini->env, node);
	return (1);
}

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

static void	print_export_error(char *arg)
{
	write(2, "minishell: export: `", 21);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}
