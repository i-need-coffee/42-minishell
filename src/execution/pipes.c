#include "minishell.h"

static int	init_pipe(t_pipe_unit *p_out, t_pipe_unit *p_in);

int	create_pipes(t_mini *mini)
{
	t_pipe_unit	*curr;

	curr = mini->units;
	while (curr)
	{
		if (curr->type == PIPE_OUT)
		{
			if (!init_pipe(curr, curr->next))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

static int	init_pipe(t_pipe_unit *p_out, t_pipe_unit *p_in)
{
	int	fds[2];

	if (pipe(fds) == -1)
	{
		perror(ERR_PIPE);
		return (0);
	}
	p_out->fd = fds[1];
	p_in->fd = fds[0];
	return (1);
}
