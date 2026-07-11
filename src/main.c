#include "minishell.h"

void	clean_unit_struct(t_pipe_unit *unit)
{
	t_pipe_unit *tmp;

	while(unit)
	{
		tmp = unit;
		unit = unit->next;
		ft_lstdelone(tmp->args, free);
		free(tmp);
		tmp = NULL;
	}
}

/*
**	Reads one line of input, validates quotes, tokenizes it, and returns
**	0 on EOF (Ctrl-D) or 1 to keep the shell loop running.
*/
// on n'inicialise pas unit ?
int	process_line(t_mini *mini)
{
	t_pipe_unit *unit;

	unit = NULL;
	mini->input = readline("minishell> ");
	if (!mini->input)
		return (0);
	if (*mini->input)
		add_history(mini->input);
	tokenize_input(mini);
	// print_tokens(&mini->tokens);
	if(parse_tokens(mini, &unit))
	{
		cleanup(mini);
		clean_unit_struct(unit);
		unit = NULL;
		return (-1);
	}
	cleanup(mini);
	clean_unit_struct(unit);
	unit = NULL;
	return (1);
}

/*
**	Entry point: initializes the shell state, builds the env list from
**	envp, configures signal handlers, then runs the read-tokenize loop
**	until EOF.
*/
int g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	ft_bzero(&mini, sizeof(t_mini));
	build_env(envp, &mini.env);
	signal_config(SIGQUIT, set_global_var);
	signal_config(SIGINT, set_global_var);
	while (process_line(&mini))
		;
//	cleanup_exit(&mini, 0);
}
