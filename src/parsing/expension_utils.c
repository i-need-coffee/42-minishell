/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:59:37 by jturrel           #+#    #+#             */
/*   Updated: 2026/09/02 22:56:49 by jturrel          ###   ########.fr       */
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

int	check_dollar_sign_number(char *str, int *i)
{
	int	dollar_num;

	dollar_num = 0;
	while (str[*i] && str[*i] == '$')
	{
		if (str[*i] == '$')
		{
			if (dollar_num == 1)
				dollar_num--;
			else
				dollar_num++;
		}
		(*i)++;
	}
	(*i)--;
	if (dollar_num > 0)
		return (1);
	return (0);
}

int	check_more(char *str, int start)
{
	if (str[start + 1])
	{
		if (str[start + 1] == '?')
			return (0);
		if (str[start + 1] == '_')
			return (0);
		if (!(ft_isalpha(str[start + 1])))
		{
			if (str[start + 1] == '\"')
			{
				if ((start - 1) >= 0 && str[start - 1] == '$')
					return (1);
				return (2);
			}
			return (1);
		}
		return (0);
	}
	return (1);
}

int	check_if_expension(char *str, int *i)
{
	int	start;
	int	ret;

	start = *i;
	if (str[*i + 1] == '$')
	{
		if (check_dollar_sign_number(str, i) == 0)
			return (1);
		start = *i;
	}
	ret = check_more(str, start);
	return (ret);
}
