#include "minishell.h"

static t_token	*create_token(t_token_type type, char *value, int expand);

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
			free(temp->value);
		free(temp);
	}
	*root = NULL;
}

int	add_token(t_token **root, t_token_type type, char *value, int expand)
{
	t_token	*new_token;
	t_token	*curr;

	new_token = create_token(type, value, expand);
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

static t_token	*create_token(t_token_type type, char *value, int expand)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("error");
		return (NULL);
	}
	ft_bzero(new_token, sizeof(t_token));
	new_token->type = type;
	if (value != NULL)
	{
		new_token->value = ft_strdup(value);
		if (!new_token->value)
		{
			perror("error");
			free(new_token);
			return (NULL);
		}
	}
	if (expand)
		new_token->expand = 1;
	return (new_token);
}
