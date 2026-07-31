#include "minishell.h"

void	increment_shell_level(t_env **env)
{
	t_env	*shlvl;
	int		nb;

	shlvl = get_env_node_with_key(env, "SHLVL");
	if (!shlvl)
		return ;
	nb = ft_atoi(shlvl->value);
	if (nb == 0)
	{
		free_and_null(&shlvl->value);
		shlvl->value = "1";
		return ;
	}
	nb++;
	free_and_null(&shlvl->value);
	shlvl->value = ft_itoa(nb);
}

/*
**	This function is used to check if there are any unclosed
**	quotes in the user input.
*/
int	has_unclosed_quotes(char *input)
{
	int	i;
	int	in_s_quotes;
	int	in_d_quotes;

	i = 0;
	in_s_quotes = 0;
	in_d_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_d_quotes)
			in_s_quotes = !in_s_quotes;
		if (input[i] == '"' && !in_s_quotes)
			in_d_quotes = !in_d_quotes;
		i++;
	}
	if (in_s_quotes || in_d_quotes)
		return (1);
	return (0);
}
