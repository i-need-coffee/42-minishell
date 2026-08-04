#include "minishell.h"

/*
**	Allocates and zero-initializes a new env node.
*/
t_env	*new_node(void)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	return (new);
}

/*
**	Appends new to the end of the env list.
*/
void	add_back(t_env **env, t_env *new)
{
	t_env	*current;

	if (!env || !new)
		return ;
	if (*env == 0)
	{
		*env = new;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	new->prev = current;
	current->next = new;
}

/*
**	Frees every node of the env list and sets *root to NULL.
*/
void	free_env(t_env **root)
{
	t_env	*curr;
	t_env	*temp;

	curr = *root;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		if (temp->key)
			free_and_null(&temp->key);
		if (temp->value)
			free_and_null(&temp->value);
		free(temp);
	}
	*root = NULL;
}

/*
**	Returns the number of nodes in the env list.
*/
int	count_env_nodes(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/*
**	Adds default PWD and SHLVL=1 nodes to env, used when envp is empty.
*/
int	add_base_env(t_env **env)
{
	t_env	*pwd;
	t_env	*shlvl;

	pwd = new_node();
	if (!pwd)
		return (0);
	pwd->key = ft_strdup("PWD");
	pwd->value = ft_strdup(get_curr_dir());
	if (!pwd->key || !pwd->value)
		return (free_and_null(&pwd->key), free_and_null(&pwd->value), free(pwd), 0);
	add_back(env, pwd);
	shlvl = new_node();
	if (!shlvl)
		return (0);
	shlvl->key = ft_strdup("SHLVL");
	shlvl->value = ft_strdup("1");
	if (!shlvl->key || !shlvl->value)
		return (free_and_null(&shlvl->key), free_and_null(&shlvl->value), free(shlvl), 0);
	add_back(env, shlvl);
	return (1);
}
