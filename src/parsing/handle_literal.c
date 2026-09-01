/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_literal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:59:45 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/25 16:59:46 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*built_first_part(char *str, char *second_part, int replace_start)
{
	char	*first_part;
	char	*tmp;

	tmp = NULL;
	first_part = NULL;
	first_part = ft_substr(str, 0, replace_start);
	if (!first_part)
		return (NULL);
	tmp = ft_strjoin(first_part, second_part);
	if (!tmp)
		return (NULL);
	free(first_part);
	first_part = NULL;
	return (tmp);
}

char	*built_last_part(char *str, char *tmp, int replace_end)
{
	char	*last_part;
	char	*joined_args;

	joined_args = NULL;
	last_part = NULL;
	last_part = ft_substr(str, replace_end, ft_strlen(str) - replace_end);
	if (!last_part)
		return (NULL);
	joined_args = ft_strjoin(tmp, last_part);
	if (!joined_args)
		return (NULL);
	free(last_part);
	last_part = NULL;
	return (joined_args);
}

int	replace_str(char **str, char *second_part, int replace_start,
		int replace_end)
{
	char	*joined_args;
	char	*tmp;
	int		ret;

	joined_args = NULL;
	tmp = NULL;
	tmp = built_first_part(*str, second_part, replace_start);
	if (!tmp)
		return (-1);
	ret = ft_strlen(tmp);
	joined_args = built_last_part(*str, tmp, replace_end);
	if (!joined_args)
	{
		free(tmp);
		tmp = NULL;
		return (-1);
	}
	free(tmp);
	tmp = NULL;
	free_and_null(str);
	*str = ft_strdup(joined_args);
	if (!*str)
		return (-1);
	free_and_null(&joined_args);
	return (ret);
}

int	replace_quote_part(char **str, int *i, t_mini *mini)
{
	char	*tmp;
	int		replace_start;

	tmp = NULL;
	replace_start = *i;
	if (wrapper_handle_quote(*str, i, mini, &tmp) == 0)
		return (-1);
	*i = replace_str(str, tmp, replace_start, *i + 1);
	if (*i == -1)
	{
		free_and_null(str);
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	}
	free_and_null(&tmp);
	return (*i);
}

int	add_arg(char **str, int i, t_pipe_unit *unit, t_mini *mini)
{
	int		start;
	char	*tmp;

	start = i;
	while (str[0][i] && str[0][i] != ' ')
	{
		if (str[0][i] == '\'' || str[0][i] == '\"')
		{
			if (replace_quote_part(str, &i, mini) == -1)
				return (-1);
			continue ;
		}
		if (str[0][i] == '$')
		{
			if (!wrapper_handle_dollar(str, &i, mini))
				return (i);
			continue ;
		}
		i++;
	}
	tmp = ft_substr(*str, start, i - start);
	if (!(create_or_update_args(unit, tmp)))
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	free_and_null(&tmp);
	return (i);
}
