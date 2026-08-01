#include "minishell.h"

int	strlen_key(char *envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	build_env(char **envp, t_env **env)
{
	int		i;
	t_env	*node;

	if (!envp || !envp[0])
	{
		if (!add_base_env(env))
			return (0);
	}
	i = 0;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (!node)
			return (0);
		add_back(env, node);
		i++;
	}
	return (1);
}

char	*get_value_with_key(t_env *env, char *key)
{
	while (env)
	{
		if (strcmp(key, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*get_env_node_with_key(t_env **root, char *key)
{
	t_env	*curr;

	curr = *root;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_env	*create_env_node(char *envp_node)
{
	t_env	*node;
	int		len_key;
	int		nb;

	len_key = strlen_key(envp_node);
	node = new_node();
	if (!node)
		return (NULL);
	node->key = ft_substr(envp_node, 0, len_key);
	node->value = ft_substr(envp_node, len_key + 1, ft_strlen(envp_node)
			- len_key);
	if (!node->key || !node->value)
		return (free(node->key), free(node->value), free(node), NULL);
	if (ft_strcmp(node->key, "SHLVL") == 0)
	{
		nb = ft_atoi(node->value);
		nb++;
		free_and_null(&node->value);
		node->value = ft_itoa(nb);
		if (!node->value)
			return (free(node->key), free(node->value), free(node), NULL);
	}
	return (node);
}
