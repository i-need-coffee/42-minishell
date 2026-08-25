/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:00:08 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/25 17:00:09 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_tokens_word_or_pipe(t_mini *mini, t_token *current, int *cmdi,
		t_pipe_unit **unit)
{
	if (current->type == TOKEN_WORD)
	{
		if (parse_word_token(unit, current, mini, *cmdi) == 0)
			return (0);
	}
	else if (current->type == TOKEN_PIPE)
	{
		if (!(parse_pipe_token(unit, current, cmdi, mini)))
			return (0);
	}
	return (1);
}

int	parse_tokens_redirection(t_mini *mini, t_token *current,
		int cmdi)
{
	if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
		|| current->type == TOKEN_APPEND || current->type == TOKEN_HEREDOC)
	{
		if (!(parse_redirection_token(current, mini, cmdi)))
		{
			mini->err_num = 2;
			return (0);
		}
	}
	return (1);
}

int	parse_tokens(t_mini *mini, t_pipe_unit **unit)
{
	t_token	*current;
	int		cmdi;

	cmdi = 0;
	current = mini->tokens;
	while (current->type != TOKEN_EOF)
	{
		if (ft_strlen(current->value) == 0)
		{
			current = current->next;
			continue ;
		}
		if (!(parse_tokens_word_or_pipe(mini, current, &cmdi, unit)))
		{
			mini->err_num = 2;
			return (0);
		}
		else if (!(parse_tokens_redirection(mini, current, cmdi)))
			return (0);
		if (*unit == NULL)
			print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
		current = current->next;
	}
	g_sig = 0;
	return (1);
}
