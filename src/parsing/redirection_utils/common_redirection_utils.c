#include "minishell.h"

void	clean_str(char *str)
{
	if (str)
	{
		ft_strlcpy(str, "", ft_strlen(str));
	}
}

int	put_value_in_prev_args(t_pipe_unit *cnode, t_token *current, t_env *env)
{
	int		i;
	char	*str;

	i = 0;
	str = current->value;
	while (str[i])
	{
		i = add_arg(&str, i, cnode, env);
		if (i == -1)
			return (0);
		while (str[i] == ' ')
			i++;
	}
	return (1);
}

int	create_redirection_node(t_pipe_unit **head, t_token *next,
		char *filename)
{
	t_pipe_unit	*tmp_unit;
	char		*buffer;

	tmp_unit = *head;
	while (tmp_unit->next)
	{
		tmp_unit = tmp_unit->next;
	}
	tmp_unit->file = filename;
	buffer = ft_strtrim(next->value, " \t");
	if (!buffer)
	{
		print_error(ERR_ALLOC);
		return (0);
	}
	free(next->value);
	next->value = NULL;
	next->value = buffer;
	return (1);
}
