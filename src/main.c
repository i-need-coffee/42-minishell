#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	*line;

	while (1)
	{
		line = readline("minishell > ");
		if (!line)
			break;
		ft_printf("you written %s\n", line);
		free(line);	
	}
	return (0);
}
