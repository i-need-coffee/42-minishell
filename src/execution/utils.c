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

void	open_files(t_pipe_unit *units)
{
	while (units)
	{
		if (units->type == REDIR_IN)
		{
			units->fd = open(units->file, O_RDONLY);
			if (units->fd == -1)
				perror(units->file);
		}
		else if (units->type == REDIR_OUT)
		{
			units->fd = open(units->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (units->fd == -1)
				perror(units->file);
		}
		else if (units->type == APPEND)
		{
			units->fd = open(units->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (units->fd == -1)
				perror(units->file);
		}
		units = units->next;
	}
}
