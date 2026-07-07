#include "minishell.h"

static int	open_file(t_pipe_unit *unit);

int	open_files(t_pipe_unit *units, int i)
{
	while (units && units->cmd_index != i)
		units = units->next;
	while (units && units->cmd_index == i)
	{
		if (!open_file(units))
			return (0);
		units = units->next;
	}
	return (1);
}

static int	open_file(t_pipe_unit *unit)
{
	int	error;

	error = 0;
	if (unit->type == REDIR_IN)
		unit->fd = open(unit->file, O_RDONLY);
	if (unit->type == REDIR_OUT)
		unit->fd = open(unit->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (unit->type == APPEND)
		unit->fd = open(unit->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (unit->fd == -1)
		error = errno;
	if (error)
	{
		print_perror(unit->file, error);
		return (0);
	}
	return (1);
}
