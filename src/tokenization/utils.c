#include "minishell.h"

static t_token	*create_token(t_token_type type, char *value);

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

void	free_tokens(t_token **root)
{
	t_token	*curr;
	t_token	*temp;

	curr = *root;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		if (temp->segments)
			free_segments(&temp->segments);
		free(temp);
	}
	*root = NULL;
}

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
		new_token->segments = generate_segments(value);
		if (!new_token->segments)
		{
			free(new_token);
			return (NULL);
		}
	}
	return (new_token);
}

void print_node(t_token *node)
{
	while(node)
	{
		ft_printf("type: %d, value: %s\n", node->type, node->value);
		node = node->next;
	}
}