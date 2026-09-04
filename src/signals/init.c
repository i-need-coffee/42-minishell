/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:00:17 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/31 20:22:45 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Sets up signal handling for the interactive prompt: SIGINT is caught
**	to redraw the prompt on a new line, SIGQUIT is ignored.
*/
void	init_signal_prompt(void)
{
	rl_catch_signals = 0;
	rl_done = 0;
	g_sig = 0;
	rl_event_hook = NULL;
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}

/*
**	Sets up signal handling for a child process running a command:
**	both SIGINT and SIGQUIT are caught by signal_handler_exec.
*/
void	init_signal_child(void)
{
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
}

/*
**	readline event hook used during heredoc input: stops readline
**	(rl_done = 1) if a SIGINT was received while waiting for a line.
*/
int	heredoc_event_hook(void)
{
	if (g_sig == SIGINT)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}
