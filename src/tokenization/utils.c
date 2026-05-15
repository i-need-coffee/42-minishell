#include "minishell.h"

static t_token	*create_token(t_token_type type, char *value, int expands);

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

int	add_token(t_token **root, t_token_type type, char *value, int expands)
{
	t_token	*new_token;
	t_token	*curr;

	new_token = create_token(type, value, expands);
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

int	has_env_variable(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$'
			&& !ft_isspace(value[i + 1]) && value[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

static t_token	*create_token(t_token_type type, char *value, int expands)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		print_error(ERR_ALLOC);
		return (NULL);
	}
	ft_bzero(new_token, sizeof(t_token));
	new_token->type = type;
	if (value != NULL)
	{
		new_token->value = ft_strdup(value);
		if (!new_token->value)
		{
			print_error(ERR_ALLOC);
			free(new_token);
			return (NULL);
		}
	}
	new_token->expands = expands;
	return (new_token);
}
