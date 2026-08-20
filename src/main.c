#include "minishell.h"

/*
**	Reads one line of input, validates quotes, tokenizes it, and returns
**	0 on EOF (Ctrl-D) or 1 to keep the shell loop running.
*/
int	process_line(t_mini *mini)
{
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
	if (!(parse_tokens(mini, &mini->units)))
	{
		cleanup(mini);
		return (1);
	}
	execute_input(mini);
	cleanup(mini);
	return (1);
}

/*
**	Entry point: initializes the shell state, builds the env list from
**	envp, configures signal handlers, then runs the read-tokenize loop
**	until EOF.
*/
int	g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	ft_bzero(&mini, sizeof(t_mini));
	mini.saved_stdin = -1;
	mini.saved_stdout = -1;
	if (!build_env(envp, &mini.env))
		print_error_and_exit(&mini, ERR_ALLOC, EXIT_FAILURE);
	signal(SIGQUIT, SIG_IGN);
	signal_config_sigint(SIGINT, handler_sigint);
	while (process_line(&mini))
		;
	cleanup_exit(&mini, 0);
}
