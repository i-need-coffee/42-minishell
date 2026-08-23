#include "minishell.h"

// void	signal_config_sigint(int signb, void (*handler_sigint)(int))
// {
// 	struct sigaction	config;
//
// 	config.sa_handler = handler_sigint;
// 	sigemptyset(&config.sa_mask);
// 	config.sa_flags = 0;
// 	if (sigaction(signb, &config, NULL) < 0)
// 		print_error(ERR_SIG);
// }

void	handler_sigint(int signb)
{
	(void)signb;
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
		set_global_var(SIGQUIT);
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
}

void	set_global_var(int signb)
{
	g_sig = signb;
}
