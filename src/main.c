#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	t_env	**env;

	(void)argc;
	(void)argv;
	env = NULL;
	env = build_env(envp, env);
	signal_config_sigquit(SIGQUIT, handler_sigquit); //obligatoire ici pour handle les signaux
	signal_config_sigint(SIGINT, handler_sigint);

	while (1)
	{
		ft_bzero(&mini, sizeof(t_mini));
		mini.input = readline("minishell> ");
		if (!mini.input)
			break ;
		if (*mini.input)
			add_history(mini.input);
		tokenize_input(&mini);
	//	print_node(mini.tokens);
		cleanup(&mini);
	}
	return (0);
}
