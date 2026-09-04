/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:00:12 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/25 17:00:13 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Appends buff_len characters from str starting at start to the
**	existing *buffer, reallocating it. Returns 1 on success, 0 on
**	allocation failure.
*/
int	wrapper_update_buffer(char **buffer, char *str, int start, int buff_len)
{
	char	*substr;
	char	*tmp_buffer;

	tmp_buffer = (char *)malloc(ft_strlen(*buffer) + 1);
	if (!tmp_buffer)
		return (0);
	ft_strlcpy(tmp_buffer, *buffer, (ft_strlen(*buffer) + 1));
	free(*buffer);
	substr = ft_substr(str, start, buff_len);
	if (!substr)
		return (0);
	*buffer = ft_strjoin(tmp_buffer, substr);
	if (!*buffer)
		return (0);
	free(substr);
	return (free(tmp_buffer), 1);
}

/*
**	Resolves the quoted section of str at *index into *tmp via
**	handle_quote, and advances *index to the matching closing quote.
**	Prints an error and returns 0 on failure, 1 on success.
*/
int	wrapper_handle_quote(char *str, int *index, t_mini *mini, char **tmp)
{
	int	i;

	i = *index;
	if ((handle_quote(str, i, mini, tmp)) == 0)
		return (print_error(ERR_QUOTES), 0);
	if (str[i] == '\'')
		*index = check_quote_sanity(str, i + 1, '\'');
	else
		*index = check_quote_sanity(str, i + 1, '\"');
	if (*index == 0)
		return (print_error(ERR_QUOTES), 0);
	return (1);
}

/*
**	If current's next token still has leftover text, ensures a CMD unit
**	exists before current_node (creating one if needed), moves the text
**	into its args, and clears the token's value. Returns 1 on success, 0
**	on failure.
*/
int	wrapper_put_value_in_prev(t_pipe_unit **head, t_token *current,
		t_mini *mini, t_pipe_unit *current_node)
{
	t_pipe_unit	*tmp_prev;

	tmp_prev = current_node->prev;
	if (ft_strlen(current->next->value) != 0)
	{
		if (!tmp_prev)
		{
			tmp_prev = new_unit_node(0, CMD);
			if (!tmp_prev)
				print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
			tmp_prev->prev = NULL;
			tmp_prev->next = current_node;
			current_node->prev = tmp_prev;
			*head = tmp_prev;
		}
		if (!(put_value_in_prev_args(tmp_prev, &current->next, mini, head)))
			return (0);
		clean_str(current->next->value);
	}
	return (1);
}

/*
**	Appends str[start:i] to *quote_buffer via create_or_update_buffer,
**	if start is at or before i. Returns 1 on success (including the
**	no-op case), 0 on allocation failure.
*/
int	wrapper_coub(char **quote_buffer, char *str, int start, int i)
{
	if (start <= i)
	{
		if ((create_or_update_buffer(quote_buffer, str, start, i)) == 0)
			return (0);
	}
	return (1);
}

/*
**	Handles the '$' at *i in *str: skips it if check_if_expension says
**	it is not a valid expansion, otherwise expands the variable
**	reference and splices the result back into *str, updating *i. Exits
**	on allocation failure.
*/
int	wrapper_handle_dollar(char **str, int *i, t_mini *mini)
{
	int		start;
	char	*tmp;
	int		flag;

	tmp = NULL;
	flag = check_if_expension(*str, i);
	if (flag > 0)
	{
		(*i)++;
		if (flag == 2)
			return (0);
		return (1);
	}
	start = *i;
	if ((*str)[*i + 1] == 0)
		return (1);
	*i = handle_dollar(*str, *(i), mini, &tmp);
	*i = replace_str(str, tmp, start, *(i));
	if (*i == -1)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	free(tmp);
	tmp = NULL;
	return (1);
}
