/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:10:08 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/25 17:10:09 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function is used to check if there are any unclosed
**	quotes in the user input.
*/
int	has_unclosed_quotes(char *input)
{
	int	i;
	int	in_s_quotes;
	int	in_d_quotes;

	i = 0;
	in_s_quotes = 0;
	in_d_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_d_quotes)
			in_s_quotes = !in_s_quotes;
		if (input[i] == '"' && !in_s_quotes)
			in_d_quotes = !in_d_quotes;
		i++;
	}
	if (in_s_quotes || in_d_quotes)
		return (1);
	return (0);
}
