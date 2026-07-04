#include "minishell.h"

static int	open_file(t_pipe_unit *unit);

int	open_files(t_pipe_unit *units, int i)
{
	while (units)
	{
		if (units->cmd_index == i)
		{
			if (!open_file(units))
				return (0);
		}
		units = units->next;
	}
	return (1);
}

static int	open_file(t_pipe_unit *unit)
{
	if (unit->type == REDIR_IN)
	{
		unit->fd = open(unit->file, O_RDONLY);
		if (unit->fd == -1)
			return (perror(unit->file), 0);
	}
	if (unit->type == REDIR_OUT)
	{
		unit->fd = open(unit->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (unit->fd == -1)
			return (perror(unit->file), 0);
	}
	if (unit->type == APPEND)
	{
		unit->fd = open(unit->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (unit->fd == -1)
			return (perror(unit->file), 0);
	}
	return (1);
}
