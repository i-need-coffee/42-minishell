#include "minishell.h"

t_env	*new_node(void)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	return (new);
}

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
			free(temp->key);
		if (temp->value)
			free(temp->value);
		free(temp);
	}
	*root = NULL;
}

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
