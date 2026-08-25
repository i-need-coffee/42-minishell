/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:59:53 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/25 16:59:54 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe_token(t_pipe_unit **unit, t_token *current, int *cmdi,
		t_mini *mini)
{
	if (current->prev == NULL || current->next == NULL)
	{
		print_error(ERR_SYNTAX_PIPE);
		return (0);
	}
	if (current->prev->type != TOKEN_WORD || current->next->type == TOKEN_PIPE
		|| current->next->type == TOKEN_EOF)
	{
		print_error(ERR_SYNTAX_PIPE);
		return (0);
	}
	if (!(create_or_update_unit_struct(unit, *cmdi, PIPE_OUT)))
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	(*cmdi)++;
	if (!(create_or_update_unit_struct(unit, *cmdi, PIPE_IN)))
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	return (1);
}
