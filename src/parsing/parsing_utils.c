#include "minishell.h"

int	wrapper_create_buffer(char **buffer, char *str, int start, int buff_len)
{
	char	*substr;

	substr = NULL;
	if (!*buffer)
	{
		*buffer = (char *)malloc((buff_len) + 1);
		if (!*buffer)
			return (0);
		substr = ft_substr(str, start, buff_len);
		if (!substr)
			return (0);
		ft_strlcpy(*buffer, substr, (buff_len) + 1);
		free(substr);
		substr = NULL;
	}
	return (1);
}

int	create_or_update_buffer(char **buffer, char *str, int start, int end)
{
	int	buff_len;

	buff_len = end - start;
	if (!*buffer)
	{
		if (!(wrapper_create_buffer(buffer, str, start, buff_len)))
			return (0);
	}
	else
	{
		if (!(wrapper_update_buffer(buffer, str, start, buff_len)))
			return (0);
	}
	return (1);
}

int	create_or_update_args(t_pipe_unit *unit, char *buffer)
{
	char	**new_args;
	int		n;
	int		i;

	if (buffer[0] == '\0')
		return (1);
	n = 0;
	if (unit->args)
		while (unit->args[n])
			n++;
	new_args = malloc(sizeof(char *) * (n + 2));
	if (!new_args)
		return (0);
	i = 0;
	while (i < n)
	{
		new_args[i] = unit->args[i];
		i++;
	}
	new_args[n] = ft_strdup(buffer);
	new_args[n + 1] = NULL;
	free(unit->args);
	unit->args = new_args;
	return (1);
}

t_pipe_unit	*new_unit_node(int cmdi, t_unit_type type)
{
	t_pipe_unit	*new_token;

	new_token = malloc(sizeof(t_pipe_unit));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->file = NULL;
	new_token->args = NULL;
	new_token->fd = -1;
	new_token->quoted_hd = 0;
	new_token->cmd_index = cmdi;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

int	create_or_update_unit_struct(t_pipe_unit **head, int cmdi,
		t_unit_type type)
{
	t_pipe_unit	*tmp;

	if (!*head)
	{
		*head = new_unit_node(cmdi, type);
		if (!*head)
			return (0);
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_unit_node(cmdi, type);
		if (!tmp->next)
			return (0);
		tmp->next->prev = tmp;
	}
	return (1);
}
