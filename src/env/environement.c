#include "minishell.h"

static int	add_base_env(t_env **env);

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
	int		len_key;

	if (!envp || !envp[0])
	{
		if (!add_base_env(env))
			return (0);
	}
	i = 0;
	while (envp[i])
	{
		len_key = strlen_key(envp[i]);
		node = new_node();
		if (!node)
			return (0);
		node->key = ft_substr(envp[i], 0, len_key);
		node->value = ft_substr(envp[i], len_key + 1, ft_strlen(envp[i])
				- len_key);
		if (!node->key || !node->value)
			return (free(node->key), free(node->value), free(node), 0);
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

static int	add_base_env(t_env **env)
{
	t_env	*pwd;
	t_env	*shlvl;

	pwd = new_node();
	if (!pwd)
		return (0);
	pwd->key = ft_strdup("PWD");
	pwd->value = ft_strdup(get_curr_dir());
	if (!pwd->key || !pwd->value)
		return (free(pwd->key), free(pwd->value), free(pwd), 0);
	add_back(env, pwd);
	shlvl = new_node();
	if (!shlvl)
		return (0);
	shlvl->key = ft_strdup("SHLVL");
	shlvl->value = ft_strdup("1");
	if (!shlvl->key || !shlvl->value)
		return (free(shlvl->key), free(shlvl->value), free(shlvl), 0);
	add_back(env, shlvl);
	return (1);
}
