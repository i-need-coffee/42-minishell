#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		ft_bzero(&mini, sizeof(t_mini));
		mini.input = readline("minishell> ");
		if (!mini.input)
			break ;
		tokenize_input(&mini);
		cleanup(&mini);
	}
	return (0);
}
