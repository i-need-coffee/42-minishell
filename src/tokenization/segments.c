#include "minishell.h"

static int	add_segment(t_token_segment **root, char *value, int quote_type);
static int	add_quoted_segment(t_token_segment **root,
				char *value, int *i, int *start);
static int	add_unquoted_segment(t_token_segment **root,
				char *value, int *i, int *start);

/*
**	Splits a token's value into a linked list of segments, each tagged
**	with its quote type (NONE, SINGLE, or DOUBLE).
*/
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
			if (!add_unquoted_segment(&root, value, &i, &start))
				return (free_segments(&root), NULL);
		}
	}
	return (root);
}

/*
**	Frees all segments in the list and sets the root pointer to NULL.
*/
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

/*
**	Allocates a new segment with the given value and quote type,
**	and appends it to the end of the list.
*/
static int	add_segment(t_token_segment **root, char *value, int quote_type)
{
	t_token_segment	*new_segment;
	t_token_segment	*curr;

	new_segment = ft_calloc(1, sizeof(t_token_segment));
	if (!new_segment)
		return (print_error(ERR_ALLOC), 0);
	new_segment->value = ft_strdup(value);
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

/*
**	Extracts the content inside the current quote pair and adds it
**	as a SINGLE or DOUBLE segment.
*/
static int	add_quoted_segment(t_token_segment **root,
	char *value, int *i, int *start)
{
	char	quote;
	char	*substr;

	quote = value[*i];
	*start = *i + 1;
	(*i)++;
	while (value[*i] && value[*i] != quote)
		(*i)++;
	substr = ft_substr(value, *start, *i - *start);
	if (!substr)
		return (print_error(ERR_ALLOC), 0);
	if (quote == '\'')
	{
		if (!add_segment(root, substr, SINGLE))
			return (free(substr), 0);
	}
	else if (quote == '"')
	{
		if (!add_segment(root, substr, DOUBLE))
			return (free(substr), 0);
	}
	free(substr);
	(*i)++;
	return (1);
}

/*
**	Extracts the plain text up to the next quote and adds it
**	as a NONE segment.
*/
static int	add_unquoted_segment(t_token_segment **root,
	char *value, int *i, int *start)
{
	char	*substr;

	*start = *i;
	while (value[*i] && value[*i] != '\'' && value[*i] != '"')
		(*i)++;
	substr = ft_substr(value, *start, *i - *start);
	if (!substr)
		return (print_error(ERR_ALLOC), 0);
	if (!add_segment(root, substr, NONE))
		return (free(substr), 0);
	free(substr);
	return (1);
}
