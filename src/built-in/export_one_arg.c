/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_one_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:11:06 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/25 17:11:07 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_values_node(t_env *curr, t_env *next);
static int	join_and_print_node(t_env *node);

/*
**	Sorts the env linked list by key using bubble sort, swapping node
**	contents in place.
*/
void	sort_env_nodes(t_env **root)
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
				swap_values_node(node, node->next);
			node = node->next;
			j++;
		}
		i++;
	}
}

/*
**	Prints every env node in "declare -x KEY="value"" format; returns 0
**	if any allocation fails.
*/
int	print_env_nodes(t_env **root)
{
	t_env	*node;

	node = *root;
	while (node)
	{
		if (!join_and_print_node(node))
			return (0);
		node = node->next;
	}
	return (1);
}

/*
**	Swaps the key and value pointers between two adjacent env nodes.
*/
static void	swap_values_node(t_env *curr, t_env *next)
{
	char	*temp;

	temp = curr->key;
	curr->key = next->key;
	next->key = temp;
	temp = curr->value;
	curr->value = next->value;
	next->value = temp;
}

/*
**	Builds the "declare -x KEY="value"" string for node and prints it,
**	freeing intermediate buffers.
*/
static int	join_and_print_node(t_env *node)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(node->value, "\"");
	if (!temp1)
		return (print_error(ERR_ALLOC_EXPORT), 0);
	temp2 = ft_strjoin("=\"", temp1);
	free_and_null(&temp1);
	if (!temp2)
		return (print_error(ERR_ALLOC_EXPORT), 0);
	temp1 = ft_strjoin(node->key, temp2);
	free_and_null(&temp2);
	if (!temp1)
		return (print_error(ERR_ALLOC_EXPORT), 0);
	temp2 = ft_strjoin("declare -x ", temp1);
	free_and_null(&temp1);
	if (!temp2)
		return (print_error(ERR_ALLOC_EXPORT), 0);
	printf("%s\n", temp2);
	free_and_null(&temp2);
	return (1);
}
