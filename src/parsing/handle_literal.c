#include "minishell.h"

int	replace_str(char **str, char *second_part, int replace_start,
		int replace_end) //message error handle
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
	if (!first_part) {
		print_error(ERR_ALLOC);
		return (0);
	}
	last_part = ft_substr(*str, replace_end, ft_strlen(*str) - replace_end);
	if (!last_part) {
		print_error(ERR_ALLOC);
		return (0);
	}
	tmp = ft_strjoin(first_part, second_part);
	if (!tmp) {
		print_error(ERR_ALLOC);
		return (0);
	}
	ret = ft_strlen(tmp);
	joined_args = ft_strjoin(tmp, last_part);
	if (!joined_args) {
		print_error(ERR_ALLOC);
		return (0);
	}
	free(tmp);
	free(first_part);
	free(second_part);
	free(last_part);
	*str = joined_args;
	return (ret);
}

int	replace_quote_part(char **str, int *i, t_env *env)//message handle error
{
	char	*tmp;
	int		replace_start;

	tmp = NULL;
	replace_start = *i;
	if (!(wrapper_handle_quote(*str, i, env, &tmp))) //MEssAGE handle error
		return (0);
	*i = replace_str(str, tmp, replace_start, *i + 1); // message handle error
	if (*i == 0)
		return (0);
	return (1);
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
			if (!(replace_quote_part(str, &i, env)))
				return (-1); // ne pas changer la valeur
			continue ;
		}
		if (str[0][i] == '$')
		{
			if (!(wrapper_handle_dollar(str, &tmp, &i, env)))
				return (-1);
			continue ;
		}
		i++;
	}
	if (!(create_or_update_args(unit, ft_substr(*str, start, i - start))))
		return (-1);
	return (i);
}
