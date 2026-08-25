/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:00:21 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/25 17:00:22 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sigint(int signb)
{
	if (signb == SIGINT)
		set_global_var(SIGINT);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_heredoc(int signb)
{
	set_global_var(signb);
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
