/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadya <shadya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:10:46 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/31 20:34:13 by shadya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc(t_pipe_unit *unit, t_mini *mini);
static int	is_limiter(char *line, char *limiter);
static char	*get_typed_line(t_pipe_unit *unit, char *delimiter, t_mini *mini);

/*
**	Processes every HEREDOC unit in the pipeline, reading its content
**	from stdin before the commands are executed.
**	The int returned here is the result of the heredoc execution (exit code)
*/
int	execute_heredocs(t_mini *mini)
{
	t_pipe_unit	*curr;

	signal(SIGINT, signal_handler_heredoc);
	rl_event_hook = heredoc_event_hook;
	curr = mini->units;
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			if (!handle_heredoc(curr, mini))
				return (1);
			if (g_sig == SIGINT)
				return (128 + SIGINT);
		}
		curr = curr->next;
	}
	init_signal_prompt();
	return (0);
}

/*
**	Reads lines from stdin into a pipe until the limiter is seen,
**	then stores the pipe's read end as unit->fd.
*/
static int	handle_heredoc(t_pipe_unit *unit, t_mini *mini)
{
	int		fds[2];
	char	*line;
	char	*typed_line;

	if (pipe(fds) == -1)
		return (perror(ERR_PIPE), 0);
	while (1)
	{
		typed_line = get_typed_line(unit, unit->file, mini);
		if (!typed_line || g_sig == SIGINT)
			break ;
		line = ft_strjoin(typed_line, "\n");
		free(typed_line);
		if (!line)
			return (close(fds[0]), close(fds[1]),
				print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE), 0);
		if (write(fds[1], line, ft_strlen(line)) == -1)
			return (perror(ERR_WRITE), free(line), close(fds[0]),
				close(fds[1]), 0);
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
	if (ft_strncmp(line, limiter, len) == 0 && (line[len] == '\n'
			|| line[len] == '\0'))
		return (1);
	return (0);
}

/*
**	Reads one line from stdin, returning NULL at EOF or if the line
**	matches delimiter (heredoc termination). If expands is set, expands
**	$VAR occurrences in the line using env.
*/
static char	*get_typed_line(t_pipe_unit *unit, char *delimiter, t_mini *mini)
{
	char	*line;
	int		i;

	line = readline("> ");
	if (!line)
		return (NULL);
	if (is_limiter(line, delimiter))
	{
		free(line);
		return (NULL);
	}
	if (unit->quoted_hd != 1)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '$')
				wrapper_handle_dollar(&line, &i, mini);
			else
				i++;
		}
	}
	return (line);
}
