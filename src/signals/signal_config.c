/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:00:21 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/31 20:23:49 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	SIGINT handler for the interactive prompt: records the signal,
**	prints "^C" on a new line, and redraws a fresh empty prompt line.
*/
void	handler_sigint(int signb)
{
	if (signb == SIGINT)
		set_global_var(SIGINT);
	write(STDOUT_FILENO, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
**	Signal handler used while reading heredoc input: records the signal
**	and prints "^C" so the interrupted heredoc read can be detected.
*/
void	signal_handler_heredoc(int signb)
{
	set_global_var(signb);
	write(STDOUT_FILENO, "^C", 2);
}

/*
**	Signal handler used while a command is executing in the shell
**	process: records SIGINT/SIGQUIT, prints the matching message, and
**	resets the prompt line.
*/
void	signal_handler_exec(int signb)
{
	if (signb == SIGINT)
		set_global_var(SIGINT);
	else if (signb == SIGQUIT)
	{
		set_global_var(SIGQUIT);
		write(STDOUT_FILENO, "Quit (core dumped)", 18);
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
}

/*
**	Stores the given signal number in the global g_sig variable so it
**	can be inspected after the signal handler returns.
*/
void	set_global_var(int signb)
{
	g_sig = signb;
}
