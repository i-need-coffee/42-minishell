/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:59:49 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/25 16:59:50 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Resets *start to *i after an expansion inside a quoted string, so
**	the next literal segment starts from the right position. Always
**	returns 1.
*/
int	increment(int *start, int *i, int *end)
{
	*start = *i;
	if (*i == *end)
		(*start)++;
	return (1);
}

/*
**	Duplicates *quote_buffer into *b and frees *quote_buffer.
*/
int	dup_and_free(char **b, char **quote_buffer)
{
	if (!*quote_buffer)
		return (0);
	*b = ft_strdup(*quote_buffer);
	free_and_null(quote_buffer);
	return (0);
}

/*
**	Parses a double-quoted string starting at i, expanding any variable
**	references inside it, and stores the result in *b. Returns the
**	index just past the closing quote, or 0 if unterminated.
*/
int	handle_double_quote(char *str, int i, t_mini *mini, char **b)
{
	int		start;
	int		end;
	char	*quote_buffer;

	start = i;
	quote_buffer = NULL;
	end = check_quote_sanity(str, i, '\"');
	if (end == 0)
		return (0);
	while (str[i] && !(i > end || i == end))
	{
		if ((str[i] == '$' && str[i + 1] != '\"' && !check_if_expension(str,
					&i)))
		{
			if ((create_or_update_buffer(&quote_buffer, str, start, i)) == 0)
				print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
			i = expension(str, i, mini, &quote_buffer);
			increment(&start, &i, &end);
		}
		i++;
	}
	if (!(wrapper_coub(&quote_buffer, str, start, i)))
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	dup_and_free(b, &quote_buffer);
	return (end + 1);
}

/*
**	Extracts the literal content of a single-quoted string (or a
**	double-quoted one, when reading a quoted heredoc delimiter) into *b
**	with no expansion. Returns the index past the closing quote, or 0
**	if unterminated.
*/
int	handle_single_quote(char *str, int i, char **b, t_mini *mini)
{
	int		end;
	char	*substr;

	i++;
	if (mini->heredoc_filename == 2)
		end = check_quote_sanity(str, i, '\"');
	else
		end = check_quote_sanity(str, i, '\'');
	if (end == 0)
		return (0);
	substr = ft_substr(str, i, end - i);
	if (!substr)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	*b = substr;
	end += 1;
	return (end);
}

/*
**	Dispatches to handle_single_quote or handle_double_quote depending
**	on the quote character at str[i] and the current heredoc-parsing
**	state. Returns 0 on failure, or the index past the closing quote.
*/
int	handle_quote(char *str, int i, t_mini *mini, char **b)
{
	if (str[i] == '\"')
	{
		if (mini->heredoc_filename == 1)
		{
			mini->heredoc_filename = 2;
			i = handle_single_quote(str, i, b, mini);
		}
		else
			i = handle_double_quote(str, i + 1, mini, b);
	}
	else
		i = handle_single_quote(str, i, b, mini);
	if (i == 0)
		return (0);
	return (i);
}
