#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	(void)envp;
	signal_config_sigquit(SIGQUIT, handler_sigquit);
	signal_config_sigint(SIGINT, handler_sigint);

	while (1)
	{
		ft_bzero(&mini, sizeof(t_mini));
		mini.input = readline("minishell> ");
		if (!mini.input)
			break ;
		tokenize_input(&mini);
	//	print_node(mini.tokens);
		cleanup(&mini);
	}
	return (0);
}
