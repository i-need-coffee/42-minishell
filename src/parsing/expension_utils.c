/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:59:37 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/25 17:00:40 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quoted_heredoc(t_mini *mini, t_token *current)
{
	t_pipe_unit	*current_unit;

	if (!(current->type == TOKEN_HEREDOC))
		return (0);
	mini->heredoc_filename = 1;
	current_unit = mini->units;
	while (current_unit->next)
	{
		current_unit = current_unit->next;
	}
	current_unit->quoted_hd = 1;
	return (1);
}

int	check_if_expension(char *str, int *i)
{
	if (str[*i + 1])
	{
		if (str[*i + 1] == '?')
			return (0);
		if (str[*i + 1] == '_')
			return (0);
		if (!(ft_isalpha(str[*i + 1])))
			return (1);
		return (0);
	}
	return (1);
}
