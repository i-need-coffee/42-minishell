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
	current->next = new;
}