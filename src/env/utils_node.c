/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:59:17 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/31 19:54:51 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
**	Creates a new node with key/value and appends it to the env list.
*/
int	add_base_node_to_env(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = new_node();
	if (!node)
		return (0);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	if (!node->value || !node->key)
		return (free(node->key), free(node->value), free(node), 0);
	add_back(env, node);
	return (1);
}
