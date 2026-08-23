#include "minishell.h"

void	init_signal_prompt(void)
{
//	write(STDOUT_FILENO, "Pouet\n", 6);
	rl_done = 0;
	g_sig = 0;
	rl_event_hook = NULL;
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal_child(void)
{
//	write(STDOUT_FILENO, "oui\n", 4);
	signal(SIGINT, signal_handler_exec);
	// signal(SIGQUIT, SIG_DFL);
//	write(STDOUT_FILENO, "ouip\n", 5);
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


