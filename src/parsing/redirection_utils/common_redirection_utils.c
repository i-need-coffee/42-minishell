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

void	clean_str(char *str)
{
	if (str)
	{
		ft_strlcpy(str, "", ft_strlen(str));
	}
}

int	put_value_in_prev_args(t_pipe_unit *cnode, t_token **current, t_mini *mini)
{
	int		i;
	char	*str;

	i = 0;
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

int	check_quote_sanity(char *str, int end, char c)
{
	while (str[end] && str[end] != c)
		end++;
	if (str[end] != c)
		return (0);
	return (end);
}
