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
		if (has_unclosed_quotes(mini.input))
		{
			ft_putstr_fd(mini.input, 2);
			ft_putstr_fd(": incorrect syntax: unclosed quotes\n", 2);
			cleanup(&mini);
			continue ;
		}
		tokenize_input(&mini);
		print_tokens(&mini.tokens);
		cleanup(&mini);
	}
	return (0);
}
