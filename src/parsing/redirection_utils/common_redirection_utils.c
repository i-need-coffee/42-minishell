/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_redirection_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:59:27 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/25 17:00:35 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Empties str in place, turning it into an empty string, if it is not
**	NULL.
*/
void	clean_str(char *str)
{
	if (str)
	{
		ft_strlcpy(str, "", ft_strlen(str));
	}
}

/*
**	Prepends a new empty CMD unit to the front of the list at head, used
**	when a redirection has no preceding command node. Exits on
**	allocation failure.
*/
void	create_cmd_node(t_pipe_unit *cnode, t_token **current,
	t_pipe_unit **head, t_mini *mini)
{
	t_pipe_unit	*tmp_unit;
	t_pipe_unit	*tmp_head;

	(void)current;
	tmp_head = *head;
	tmp_unit = cnode->prev;
	if ((tmp_unit))
	{
		while (tmp_unit->prev != NULL)
			tmp_unit = tmp_unit->prev;
	}
	tmp_unit = new_unit_node(0, CMD);
	if (!tmp_unit)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	tmp_unit->prev = NULL;
	tmp_unit->next = tmp_head;
	*head = tmp_unit;
}

/*
**	Ensures cnode is a CMD unit (creating one via create_cmd_node if
**	not), then splits (*current)'s value into arguments, resolving
**	quotes and expansions, appending each to cnode's args. Returns 1 on
**	success, 0 on failure.
*/
int	put_value_in_prev_args(t_pipe_unit *cnode, t_token **current,
	t_mini *mini, t_pipe_unit **head)
{
	int		i;
	char	*str;

	i = 0;
	if (cnode->type != CMD)
	{
		create_cmd_node(cnode, current, head, mini);
		cnode = mini->units;
	}
	str = (*current)->value;
	while (str[i])
	{
		i = add_arg(&str, i, cnode, mini);
		if (i == -1)
			return (0);
		while (str[i] == ' ')
			i++;
	}
	(*current)->value = str;
	return (1);
}

/*
**	Attaches filename to the last unit in the list at head, and trims
**	next's value down to whatever text remains after the filename.
**	Returns 1 on success, 0 on allocation failure.
*/
int	create_redirection_node(t_pipe_unit **head, t_token *next,
		char *filename)
{
	t_pipe_unit	*tmp_unit;
	char		*buffer;

	tmp_unit = *head;
	while (tmp_unit->next)
	{
		tmp_unit = tmp_unit->next;
	}
	tmp_unit->file = filename;
	buffer = ft_strtrim(next->value, " \t");
	if (!buffer)
		return (0);
	free(next->value);
	next->value = NULL;
	next->value = buffer;
	return (1);
}

/*
**	Scans str from end for the next occurrence of c. Returns its index,
**	or 0 if c is not found (unterminated quote).
*/
int	check_quote_sanity(char *str, int end, char c)
{
	while (str[end] && str[end] != c)
		end++;
	if (str[end] != c)
		return (0);
	return (end);
}
