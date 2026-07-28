#include "minishell.h"

static int	init_pipe(t_pipe_unit *p_out, t_pipe_unit *p_in);

/*
**	Creates a pipe for each PIPE_OUT unit in the pipeline, linking it
**	to the following PIPE_IN unit.
*/
int	create_pipes(t_mini *mini)
{
	t_pipe_unit	*curr;

	curr = mini->units;
	while (curr)
	{
		if (curr->type == PIPE_OUT)
		{
			if (!init_pipe(curr, curr->next))
			{
				mini->err_num = 1;
				return (0);
			}
		}
		curr = curr->next;
	}
	return (1);
}

/*
**	Opens one pipe and assigns its write end to p_out and its read
**	end to p_in.
*/
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
