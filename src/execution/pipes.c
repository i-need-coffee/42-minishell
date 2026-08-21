#include "minishell.h"

int create_pipe(t_mini *mini, int i)
{
	int			fds[2];
	t_pipe_unit *curr;

	if (pipe(fds) == -1)
		return (perror(ERR_PIPE), 0);
	curr = mini->units;
	while (curr && curr->cmd_index != i)
		curr = curr->next;
	while (curr && curr->cmd_index == i)
	{
		if (curr->type == PIPE_OUT)
			curr->fd = fds[1];
		curr = curr->next;
	}
	while (curr && curr->cmd_index == i + 1)
	{
		if (curr->type == PIPE_IN)
			curr->fd = fds[0];
		curr = curr->next;
	}
	return (1);
}
