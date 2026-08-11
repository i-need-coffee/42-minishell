#include "minishell.h"

int	quoted_heredoc(t_mini *mini, t_token *current)
{
	if (current->type == TOKEN_HEREDOC)
		mini->quoted_hd = 1;
	return (0);
}

int	check_if_expension(char *str, int *i)
{
	if (str[*i + 1])
	{
		if (str[*i + 1] == '?')
			return (0);
		if (str[*i + 1] == '_')
			return (0);
		if (!(ft_isalpha(str[*i + 1])))
			return (1);
		return (0);
	}
	return (1);
}
