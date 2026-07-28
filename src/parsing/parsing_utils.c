#include "minishell.h"

void	create_or_update_buffer(char **buffer, char *str, int start, int end)
{
	char	*substr;
	char	*tmp_buffer;

	if (!*buffer)
	{
		*buffer = (char *)malloc((end - start) + 1);
		if (!*buffer)
			ft_abort("Memory allocation failed");
		substr = ft_substr(str, start, end - start);
		ft_strlcpy(*buffer, substr, (end - start) + 1);
		free(substr);
	}
	else
	{
		tmp_buffer = (char *)malloc(ft_strlen(*buffer) + 1);
		if (!tmp_buffer)
			ft_abort("Memory allocation failed");
		ft_strlcpy(tmp_buffer, *buffer, (ft_strlen(*buffer) + 1));
		free(*buffer);
		substr = ft_substr(str, start, end - start);
		*buffer = ft_strjoin(tmp_buffer, substr);
		free(substr);
		free(tmp_buffer);
	}
}

void	create_or_update_args(t_pipe_unit *unit, char *buffer)
{
	char	**new_args;
	int		n;
	int		i;

	n = 0;
	if (unit->args)
		while (unit->args[n])
			n++;
	new_args = malloc(sizeof(char *) * (n + 2));
	if (!new_args)
		ft_abort("Memory allocation failed");
	i = 0;
	while (i < n)
	{
		new_args[i] = unit->args[i];
		i++;
	}
	new_args[n] = buffer;
	new_args[n + 1] = NULL;
	free(unit->args);
	unit->args = new_args;
}

t_pipe_unit	*new_unit_node(int cmdi, t_unit_type type)
{
	t_pipe_unit	*new_token;

	new_token = malloc(sizeof(t_pipe_unit));
	if (!new_token)
		ft_abort("Memory allocation failed");
	new_token->type = type;
	new_token->file = NULL;
	new_token->args = NULL;
	new_token->fd = -1;
	new_token->cmd_index = cmdi;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

// inicialise une node et l'ajoute a la chaine
// TODO: return re-type and handle error
t_pipe_unit	*create_or_update_unit_struct(t_pipe_unit **head, int cmdi,
		t_unit_type type)
{
	t_pipe_unit	*tmp;

	if (!*head)
		*head = new_unit_node(cmdi, type);
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_unit_node(cmdi, type);
		tmp->next->prev = tmp;
	}
	return (NULL);
}
