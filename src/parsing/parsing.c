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

/*
**	Dispatches current to parse_word_token or parse_pipe_token depending
**	on its token type. Returns 1 on success, 0 on failure.
*/
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

/*
**	If current is a redirection token, parses it via
**	parse_redirection_token and sets mini->err_num on failure. Returns 1
**	on success, 0 on failure.
*/
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

/*
**	Walks mini's token list, parsing each word, pipe and redirection
**	token into unit, and skipping empty word tokens. Returns 1 on
**	success, 0 on syntax or allocation error.
*/
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
