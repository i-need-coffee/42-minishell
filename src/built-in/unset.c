#include "minishell.h"

static void	remove_env_node(t_env *curr, t_env **root);

int	unset(t_env **root, char **args)
{
	t_env	*curr;
	int		i;

	i = 1;
	while (args[i])
	{
		curr = *root;
		while (curr != NULL)
		{
			if (ft_strcmp(args[i], curr->key) == 0)
			{
				if (curr == *root && curr->next == NULL)
					return (free_env(root), 0);
				remove_env_node(curr, root);
				break ;
			}
			curr = curr->next;
		}
		i++;
	}
	return (0);
}

static void	remove_env_node(t_env *curr, t_env **root)
{
	t_env	*temp;

	if (curr == *root)
	{
		*root = curr->next;
		(*root)->prev = NULL;
	}
	else
	{
		if (curr->prev)
			curr->prev->next = curr->next;
		if (curr->next)
			curr->next->prev = curr->prev;
	}
	temp = curr;
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
	free(temp);
}
