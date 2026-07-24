#include "minishell.h"

static void	sort_nodes(t_env **root);
static void	swap_nodes(t_env *curr, t_env *next);
static void	print_nodes(t_mini *mini);
static int	add_node_to_env(t_mini *mini, char *arg);
static int	is_key_valid(char *key);
static void	print_export_error(char *arg);

int	export(t_mini *mini, char **args)
{
	int	i;

	if (count_args(args) == 1)
	{
		sort_nodes(&mini->env);
		print_nodes(mini);
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

static void	sort_nodes(t_env **root)
{
	t_env	*node;
	int		i;
	int		j;
	int		count;

	i = 0;
	count = count_env_nodes(*root);
	while (i < count - 1)
	{
		node = *root;
		j = 0;
		while (j < (count - i - 1))
		{
			if (node && node->next && ft_strcmp(node->key, node->next->key) > 0)
				swap_nodes(node, node->next);
			node = node->next;
			j++;
		}
		i++;
	}
}

static void	swap_nodes(t_env *curr, t_env *next)
{
	char	*temp;

	temp = curr->key;
	curr->key = next->key;
	next->key = temp;
	temp = curr->value;
	curr->value = next->value;
	next->value = temp;
}

static void	print_nodes(t_mini *mini)
{
	char	*temp1;
	char	*temp2;

	while (mini->env)
	{
		temp1 = ft_strjoin(mini->env->value, "\"");
		if (!temp1)
			print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
		temp2 = ft_strjoin("=\"", temp1);
		free_and_null(&temp1);
		if (!temp2)
			print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
		temp1 = ft_strjoin(mini->env->key, temp2);
		free_and_null(&temp2);
		if (!temp1)
			print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
		temp2 = ft_strjoin("declare -x ", temp1);
		free_and_null(&temp1);
		if (!temp2)
			print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
		printf("%s\n", temp2);
		free_and_null(&temp2);
		mini->env = mini->env->next;
	}
}

static int	add_node_to_env(t_mini *mini, char *arg)
{
	char	*key;
	char	*value;

	if (!ft_strchr(arg, '='))
	{
		key = ft_strdup(arg);
		value = ft_strdup("\0");
	}
	else
		set_values(&key, &value);
	if (!key || !value)
	{
		
	}
	return (1);
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
