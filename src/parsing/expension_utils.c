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

/*
**	If current is a heredoc token, flags the last pipe unit as having a
**	quoted heredoc delimiter. Returns 1 if applied, 0 otherwise.
*/
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

/*
**	Advances *i over a run of consecutive '$' characters, leaving it on
**	the last one. Returns 1 if the run has an odd length, 0 otherwise.
*/
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

/*
**	Checks whether the character following str[start] can start a
**	variable name. Returns 0 if it can (expansion applies), 1 if the
**	'$' is literal, or 2 for a literal '$' immediately before a quote.
*/
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

/*
**	Determines whether the '$' at *i introduces a variable expansion,
**	first collapsing any run of consecutive '$' characters. Returns 0
**	if expansion applies, 1 or 2 if the '$' should be treated literally.
*/
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
