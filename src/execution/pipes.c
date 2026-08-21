#include "minishell.h"

void	init_pipe_units(t_pipe_unit **root, int i, int *fd_out, int *fd_in)
{
	t_pipe_unit *curr;

	curr = *root;
	while (curr && curr->cmd_index != i)
		curr = curr->next;
	while (curr && curr->cmd_index == i)
	{
		if (curr->type == PIPE_OUT)
			curr->fd = *fd_out;
		curr = curr->next;
	}
	while (curr && curr->cmd_index == i + 1)
	{
		if (curr->type == PIPE_IN)
			curr->fd = *fd_in;
		curr = curr->next;
	}
}
