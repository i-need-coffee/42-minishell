/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:00:17 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/30 16:19:13 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signal_prompt(void)
{
	rl_done = 0;
	g_sig = 0;
	rl_event_hook = NULL;
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal_child(void)
{
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
}

int	heredoc_event_hook(void)
{
	if (g_sig == SIGINT)
	{
		rl_done = 1;
		return (1);
	}
	return (0);
}
