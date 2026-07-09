#include "minishell.h"

void	free_pipe_units(t_pipe_unit **root)
{
	t_pipe_unit	*curr;
	t_pipe_unit	*temp;

	curr = *root;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		if (temp->file)
			free(temp->file);
		if (temp->args)
			free_char_tab(temp->args);
		safe_close(&temp->fd);
		free(temp);
	}
	*root = NULL;
}

void	close_all_fds(t_pipe_unit *units)
{
	while (units)
	{
		safe_close(&units->fd);
		units = units->next;
	}
}

t_pipe_unit	*get_cmd_unit(t_pipe_unit *units, int i)
{
	while (units && units->cmd_index != i)
		units = units->next;
	while (units && units->cmd_index == i)
	{
		if (units->type == CMD)
			return (units);
		units = units->next;
	}
	return (NULL);
}
