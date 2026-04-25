#include "minishell.h"

static t_token	*create_token(t_token_type type, t_quotes quotes, char *value);

void	print_tokens(t_token **root)
{
	t_token	*curr;

	curr = *root;
	ft_printf("-- TOKENS START --\n");
	while (curr->type != TOKEN_EOF)
	{
		ft_printf("TYPE: %d, VALUE: %s, QUOTES: %d\n", curr->type, curr->value, curr->quotes);
		curr = curr->next;
	}
	ft_printf("-- TOKENS END --\n");
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
		if (temp->value)
			free(temp->value);
		free(temp);
	}
	*root = NULL;
}

int	add_token(t_token **root, t_token_type type, t_quotes quotes, char *value)
{
	t_token	*new_token;
	t_token	*curr;

	new_token = create_token(type, quotes, value);
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

static t_token	*create_token(t_token_type type, t_quotes quotes, char *value)
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
	new_token->quotes = quotes;
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
	return (new_token);
}
