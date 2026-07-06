#include "minishell.h"

static int	handle_heredoc(t_pipe_unit *unit);
static int	is_limiter(char *line, char *limiter);

int	execute_heredocs(t_mini *mini)
{
	t_pipe_unit	*curr;

	curr = mini->units;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			if (!handle_heredoc(curr))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

static int	handle_heredoc(t_pipe_unit *unit)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
	{
		perror(ERR_PIPE);
		return (0);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (is_limiter(line, unit->file))
		{
			free(line);
			break ;
		}
		write(fds[1], line, ft_strlen(line));
		free(line);
	}
	close(fds[1]);
	unit->fd = fds[0];
	return (1);
}

static int	is_limiter(char *line, char *limiter)
{
	size_t	len;

	len = ft_strlen(limiter);
	if (ft_strncmp(line, limiter, len) == 0
		&& (line[len] == '\n' || line[len] == '\0'))
		return (1);
	return (0);
}
