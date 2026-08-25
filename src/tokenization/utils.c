/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:10:26 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/25 17:10:27 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_token(t_token_type type, char *value);

/*
**	Allocates a new token and appends it to the end of the token list.
**	Returns 1 on success, 0 on allocation failure.
*/
int	add_token(t_token **root, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*curr;

	new_token = create_token(type, value);
	if (!new_token)
		return (0);
	if (!*root)
	{
		*root = new_token;
		return (1);
	}
	curr = *root;
	while (curr->next)
		curr = curr->next;
	curr->next = new_token;
	new_token->prev = curr;
	return (1);
}

/*
**	Frees all tokens in the list and sets the root pointer to NULL.
*/
void	free_tokens(t_token **root)
{
	t_token	*curr;
	t_token	*temp;

	curr = *root;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		if (temp->value)
			free_and_null(&temp->value);
		free(temp);
	}
	*root = NULL;
}

/*
**	Allocates a token with the given type and generates its segment list
**	from value. Returns NULL on allocation failure.
*/
static t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		print_error(ERR_ALLOC);
		return (NULL);
	}
	new_token->type = type;
	if (value)
	{
		new_token->value = ft_strdup(value);
		if (!new_token->value)
		{
			free(new_token);
			return (NULL);
		}
	}
	return (new_token);
}
