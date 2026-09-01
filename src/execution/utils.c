/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjolliet <sjolliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:10:48 by sjolliet          #+#    #+#             */
/*   Updated: 2026/09/01 17:22:28 by sjolliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Frees every pipe_unit in the list, closing its fd and releasing
**	its file/args, then nulls *root.
*/
void	free_pipe_units(t_pipe_unit **root)
{
	t_pipe_unit	*curr;
	t_pipe_unit	*temp;

	curr = *root;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		if (temp->file)
			free(temp->file);
		if (temp->args)
			free_char_tab(temp->args);
		safe_close(&temp->fd);
		free(temp);
	}
	*root = NULL;
}

/*
**	Closes every unit's fd across the whole pipeline and in the mini struct.
*/
void	close_all_fds(t_mini *mini)
{
	t_pipe_unit	*curr;

	curr = mini->units;
	while (curr)
	{
		safe_close(&curr->fd);
		curr = curr->next;
	}
	close_pipe_fds(mini);
}

/*
**	Closes fds linked to pipes in the mini struct.
*/
void	close_pipe_fds(t_mini *mini)
{
	safe_close(&mini->fds[0]);
	safe_close(&mini->fds[1]);
	safe_close(&mini->old_rd_fd);
}

/*
**	Returns the CMD-type unit belonging to command index i, or NULL
**	if that command has none.
*/
t_pipe_unit	*get_cmd_unit(t_pipe_unit *units, int i)
{
	while (units && units->cmd_index != i)
		units = units->next;
	while (units && units->cmd_index == i)
	{
		if (units->type == CMD)
			return (units);
		units = units->next;
	}
	return (NULL);
}

/*
**	Check if cmd exists and if it has args.
*/
int	is_cmd_empty(t_pipe_unit *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	return (0);
}
