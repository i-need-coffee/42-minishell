#include "minishell.h"

int	replace_str(char **str, char *second_part, int replace_start,
		int replace_end)
{
	char	*first_part;
	char	*joined_args;
	char	*last_part;
	char	*tmp;
	int		ret;

	joined_args = NULL;
	first_part = NULL;
	last_part = NULL;
	first_part = ft_substr(*str, 0, replace_start);
	last_part = ft_substr(*str, replace_end, ft_strlen(*str) - replace_end);
	tmp = ft_strjoin(first_part, second_part);
	ret = ft_strlen(tmp);
	joined_args = ft_strjoin(tmp, last_part);
	free(tmp);
	free(first_part);
	free(second_part);
	free(last_part);
	*str = joined_args;
	return (ret);
}

int	replace_quote_part(char **str, int *i, t_env *env)
{
	char	*tmp;
	int		replace_start;

	tmp = NULL;
	replace_start = *i;
	if (wrapper_handle_quote(*str, i, env, &tmp))
		return (-1);
	*i = replace_str(str, tmp, replace_start, *i + 1);
	return (0);
}

int	add_arg(char **str, int i, t_pipe_unit *unit, t_env *env)
{
	int		start;
	char	*tmp;

	tmp = NULL;
	start = i;
	while (str[0][i] && str[0][i] != ' ')
	{
		if (str[0][i] == '\'' || str[0][i] == '\"')
		{
			if (replace_quote_part(str, &i, env))
				return (-1);
			continue ;
		}
		if (str[0][i] == '$')
		{
			wrapper_handle_dollar(str, &tmp, &i, env);
			continue ;
		}
		i++;
	}
	create_or_update_args(unit, ft_substr(*str, start, i - start));
	return (i);
}
