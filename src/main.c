#include "minishell.h"

/*
**	Reads one line of input, validates quotes, tokenizes it, and returns
**	0 on EOF (Ctrl-D) or 1 to keep the shell loop running.
*/
int	process_line(t_mini *mini)
{
	ft_printf("last error num: %d\n", mini->err_num);
	mini->input = readline("minishell> ");
	if (!mini->input)
		return (0);
	if (*mini->input)
		add_history(mini->input);
	if (has_unclosed_quotes(mini->input))
	{
		mini->err_num = 2;
		return (print_error(ERR_QUOTES), cleanup(mini), 1);
	}
	tokenize_input(mini);
	if (!execute_input(mini))
		return (cleanup(mini), 1);
	cleanup(mini);
	return (1);
}

/*
**	Entry point: initializes the shell state, builds the env list from
**	envp, configures signal handlers, then runs the read-tokenize loop
**	until EOF.
*/
int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	ft_bzero(&mini, sizeof(t_mini));
	build_env(envp, &mini.env);
	signal_config_sigquit(SIGQUIT, handler_sigquit);
	signal_config_sigint(SIGINT, handler_sigint);
	while (process_line(&mini))
		;
	cleanup_exit(&mini, 0);
}
