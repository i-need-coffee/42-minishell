#include "minishell.h"

void	signal_config(int signb, void *handler)
{
	struct sigaction	config;

	config.sa_handler = handler;
	sigemptyset(&config.sa_mask);
	config.sa_flags = 0;
	if (sigaction(signb, &config, NULL) < 0)
		print_error(ERR_SIGACTION);
}

void	handler_sigint(int signb)
{
	(void)signb;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handler_sigquit(int signb)
{
	(void)signb;
	rl_on_new_line();
	rl_redisplay();
}

void	set_global_var(int signb)
{
	g_sig = signb;
}
