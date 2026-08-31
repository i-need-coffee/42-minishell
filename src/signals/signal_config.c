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

void	handler_sigint(int signb)
{
	if (signb == SIGINT)
		set_global_var(SIGINT);
	write(STDOUT_FILENO, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_heredoc(int signb)
{
	set_global_var(signb);
	write(STDOUT_FILENO, "^C", 2);
}

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

void	set_global_var(int signb)
{
	g_sig = signb;
}
