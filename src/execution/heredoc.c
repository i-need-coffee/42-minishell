#include "minishell.h"

static void	remove_delimiter_quotes(char *str, char **new_str);
static int	handle_heredoc(t_pipe_unit *unit, t_mini *mini, int expands);
static int	is_limiter(char *line, char *limiter);
static char	*get_typed_line(char *delimiter, int expands, t_mini *mini);

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
			if (ft_strchr(curr->file, '\'') || ft_strchr(curr->file, '"'))
				expands = 0;
			remove_delimiter_quotes(curr->file, &delimiter);
			if (!delimiter)
				print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
			free_and_null(&curr->file);
			curr->file = delimiter;
			if (!handle_heredoc(curr, mini, expands))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

/*
** Copies str into new_str, stripping every single and double quote.
** Used because the heredoc delimiter is matched literally.
*/
static void	remove_delimiter_quotes(char *str, char **new_str)
{
	int		i;
	int		j;
	int		str_len;

	i = 0;
	str_len = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			str_len++;
		i++;
	}
	*new_str = malloc((str_len + 1) * sizeof(char));
	if (!*new_str)
		return ;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			(*new_str)[j++] = str[i];
		i++;
	}
	(*new_str)[j] = '\0';
}

/*
**	Reads lines from stdin into a pipe until the limiter is seen,
**	then stores the pipe's read end as unit->fd.
*/
static int	handle_heredoc(t_pipe_unit *unit, t_mini *mini, int expands)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (perror(ERR_PIPE), 0);
	while (1)
	{
		if (write(1, "> ", 2) == -1)
			return (print_error(ERR_WRITE), close(fds[0]), close(fds[1]), 0);
		line = get_typed_line(unit->file, expands, mini);
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

/*
**	Reads one line from stdin, returning NULL at EOF or if the line
**	matches delimiter (heredoc termination). If expands is set, expands
**	$VAR occurrences in the line using env.
*/
static char	*get_typed_line(char *delimiter, int expands, t_mini *mini)
{
	char	*line;
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
			if (line[i] == '$' && line[i + 1])
				wrapper_handle_dollar(&line, &i, mini);
			else
				i++;
		}
	}
	return (line);
}
