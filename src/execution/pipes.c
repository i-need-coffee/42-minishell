#include "minishell.h"

static int	init_pipe(t_pipe_unit **p_out, t_pipe_unit **p_in);

int	create_pipe(t_mini *mini, t_pipe_unit *units, int i)
{
	t_pipe_unit	*p_out;
	t_pipe_unit	*p_in;

	while (units && units->cmd_index != i)
		units = units->next;
	while (units && units->cmd_index == i)
	{
		if (units->type == PIPE_OUT)
			p_out = units;
		units = units->next;
	}
	while (units && units->cmd_index == i + 1)
	{
		if (units->type == PIPE_IN)
			p_in = units;
		units = units->next;
	}
	if (!init_pipe(&p_out, &p_in))
	{
		mini->err_num = 1;
		return (0);
	}
	return (1);
}

/*
**	Opens one pipe and assigns its write end to p_out and its read
**	end to p_in.
*/
static int	init_pipe(t_pipe_unit **p_out, t_pipe_unit **p_in)
{
	int	fds[2];

	if (pipe(fds) == -1)
	{
		perror(ERR_PIPE);
		return (0);
	}
	(*p_out)->fd = fds[1];
	(*p_in)->fd = fds[0];
	return (1);
}
