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
	char	*tmp;
	char	*str;

	tmp = NULL;
	i = 0;
	str = current->value;
	while (str[i])
	{
		i = add_arg(&str, i, cnode, env);
		if (i == -1)
			return (-1);
		while (str[i] == ' ')
			i++;
	}
	return (0);
}

void	create_redirection_node(t_pipe_unit **head, t_token *next,
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
	free(next->value);
	next->value = NULL;
	next->value = buffer;
}
