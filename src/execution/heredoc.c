#include "minishell.h"

static int	handle_heredoc(t_pipe_unit *unit, t_env *env, int expands);
static int	is_limiter(char *line, char *limiter);
static char	*get_typed_line(char *delimiter, int expands, t_env *env);

/*
**	Processes every HEREDOC unit in the pipeline, reading its content
**	from stdin before the commands are executed.
*/
int	execute_heredocs(t_mini *mini)
{
	t_pipe_unit	*curr;
	char		*delimiter;
	int			expands;

	curr = mini->units;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			expands = 1;
			if (curr->file[0] == '\'' || curr->file[0] == '"')
				expands = 0;
			delimiter = ft_strtrim(curr->file, "'\"");
			if (!delimiter)
				print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
			free_and_null(&curr->file);
			curr->file = delimiter;
			if (!handle_heredoc(curr, mini->env, expands))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

/*
**	Reads lines from stdin into a pipe until the limiter is seen,
**	then stores the pipe's read end as unit->fd.
*/
static int	handle_heredoc(t_pipe_unit *unit, t_env *env, int expands)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (perror(ERR_PIPE), 0);
	while (1)
	{
		if (write(1, "> ", 2) == -1)
			return (print_error(ERR_WRITE), close(fds[0]), close(fds[1]), 0);
		line = get_typed_line(unit->file, expands, env);
		if (!line)
			break ;
		if (write(fds[1], line, ft_strlen(line)) == -1)
			return (print_error(ERR_WRITE),
				free(line), close(fds[0]), close(fds[1]), 0);
		free(line);
	}
	close(fds[1]);
	unit->fd = fds[0];
	return (1);
}

/*
**	Returns 1 if line matches limiter exactly (up to a trailing
**	newline or end of string), 0 otherwise.
*/
static int	is_limiter(char *line, char *limiter)
{
	size_t	len;

	len = ft_strlen(limiter);
	if (ft_strncmp(line, limiter, len) == 0
		&& (line[len] == '\n' || line[len] == '\0'))
		return (1);
	return (0);
}

static char	*get_typed_line(char *delimiter, int expands, t_env *env)
{
	char	*line;
	char	*temp;
	int		i;

	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	if (is_limiter(line, delimiter))
	{
		free(line);
		return (NULL);
	}
	if (expands)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '$' && !(
					wrapper_handle_dollar(&line, &temp, &i, env)))
				break ;
			else if (line[i] != '$')
				i++;
		}
	}
	return (line);
}
