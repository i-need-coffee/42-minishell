/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:10:44 by sjolliet          #+#    #+#             */
/*   Updated: 2026/08/25 17:10:45 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(t_pipe_unit *unit);

/*
**	Opens every redirection file belonging to command i, storing each
**	resulting fd on its unit.
*/
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

/*
**	Opens unit's file with the flags matching its redirection type
**	(REDIR_IN/REDIR_OUT/APPEND) and stores the fd on the unit.
*/
static int	open_file(t_pipe_unit *unit)
{
	int	error;

	error = 0;
	if (unit->type == REDIR_IN)
		unit->fd = open(unit->file, O_RDONLY);
	else if (unit->type == REDIR_OUT)
		unit->fd = open(unit->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (unit->type == APPEND)
		unit->fd = open(unit->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (1);
	if (unit->fd == -1)
		error = errno;
	if (error)
	{
		print_error3("minishell", unit->file, strerror(error));
		return (0);
	}
	return (1);
}
