#include "minishell.h"

static int	add_segment(t_token_segment **root, char *value,
				int start, int end, int quote_type);
static int	add_quoted_segment(t_token_segment **root, char *value, int *i, int *start);

t_token_segment	*generate_segments(char *value)
{
	t_token_segment	*root;
	int				i;
	int				start;

	root = NULL;
	i = 0;
	start = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
		{
			if (!add_quoted_segment(&root, value, &i, &start))
				return (free_segments(&root), NULL);
		}
		else
		{
			start = i;
			while (value[i] && value[i] != '\'' && value[i] != '"')
				i++;
			if (!add_segment(&root, value, start, i, NONE))
				return (free_segments(&root), NULL);
		}
	}
	return (root);
}

void	free_segments(t_token_segment **root)
{
	t_token_segment	*curr;
	t_token_segment	*temp;

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

static int	add_segment(t_token_segment **root, char *value,
	int start, int end, int quote_type)
{
	t_token_segment	*new_segment;
	t_token_segment	*curr;

	new_segment = ft_calloc(1, sizeof(t_token_segment));
	if (!new_segment)
		return (print_error(ERR_ALLOC), 0);
	new_segment->value = ft_substr(value, start, end - start);
	if (!new_segment->value)
		return (print_error(ERR_ALLOC), free(new_segment), 0);
	new_segment->quote_type = quote_type;
	if (!*root)
	{
		*root = new_segment;
		return (1);
	}
	curr = *root;
	while (curr->next)
		curr = curr->next;
	curr->next = new_segment;
	return (1);
}

static int	add_quoted_segment(t_token_segment **root, char *value, int *i, int *start)
{
	char	quote;

	quote = value[*i];
	*start = *i + 1;
	(*i)++;
	while (value[*i] && value[*i] != quote)
		(*i)++;
	if (quote == '\'')
	{
		if (!add_segment(root, value, *start, *i, SINGLE))
			return (0);
	}
	else if (quote == '"')
	{
		if (!add_segment(root, value, *start, *i, DOUBLE))
			return (0);
	}
	(*i)++;
	return (1);
}
