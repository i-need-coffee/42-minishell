/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:59:57 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/25 16:59:58 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Splits *str at index i: returns the prefix as a newly allocated
**	string and stores the suffix into *next_value, replacing its
**	previous content. Exits on allocation failure.
*/
char	*put_rest_on_value(char **str, int i, char **next_value, t_mini *mini)
{
	char	*rest;
	char	*substr;

	rest = NULL;
	substr = NULL;
	substr = ft_substr(*str, 0, i);
	if (!substr)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	rest = ft_substr(*str, i, ft_strlen(*str) - i);
	if (!rest)
	{
		free(substr);
		substr = NULL;
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	}
	free(*next_value);
	*next_value = NULL;
	*next_value = rest;
	return (substr);
}

/*
**	Resolves the quoted section of *str at *i, replacing it in place
**	with its unquoted content, and updates *i accordingly. Returns 1 on
**	success, 0 on failure.
*/
int	quote_part(char **str, int *i, t_mini *mini)
{
	char	*substr;
	char	*tmp;
	int		start;

	start = 0;
	tmp = NULL;
	substr = NULL;
	start = *i;
	substr = ft_substr(*str, 0, *i);
	if (!substr)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	if (!(wrapper_handle_quote(*str, i, mini, &tmp)))
		return (0);
	*i = replace_str(str, tmp, start, *(i) + 1);
	free(tmp);
	tmp = NULL;
	free(substr);
	substr = NULL;
	if (*i == -1)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	return (1);
}

/*
**	Scans *str for the redirection target, resolving quotes and (unless
**	this is a heredoc) variable expansions, up to the first unquoted
**	space. Returns the resolved filename, or NULL on failure.
*/
char	*get_file_name(t_mini *mini, char **next_value, char **str,
		t_token *current)
{
	int		i;
	char	*substr;

	i = 0;
	substr = NULL;
	while ((*str)[i] != '\0' && (*str)[i] != ' ')
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
		{
			quoted_heredoc(mini, current);
			if (!quote_part(str, &i, mini))
				return (NULL);
			continue ;
		}
		if (str[0][i] == '$' && (current->type != TOKEN_HEREDOC))
		{
			wrapper_handle_dollar(str, &i, mini);
			continue ;
		}
		i++;
	}
	substr = put_rest_on_value(str, i, next_value, mini);
	return (substr);
}

/*
**	Adds a redirection unit of type to the command list for cmdi,
**	resolves its target filename from the token after current, and
**	attaches the result (plus any leftover arguments) to the right
**	command. Returns 1 on success, 0 on failure.
*/
int	uptade_unit_struct_redir(t_mini *mini, t_token *current, t_unit_type type,
		int cmdi)
{
	t_pipe_unit	*current_node;
	char		*str;
	char		*file_name;
	t_pipe_unit	**head;

	head = &mini->units;
	if (!(create_or_update_unit_struct(head, cmdi, type)))
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	str = ft_strdup(current->next->value);
	if (!str)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	current_node = *head;
	while (current_node->next)
		current_node = current_node->next;
	file_name = get_file_name(mini, &current->next->value, &str, current);
	if (!file_name)
		return (free_and_null(&str), 0);
	if (!(create_redirection_node(head, current->next, file_name)))
	{
		free_and_null(&str);
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	}
	if (!(wrapper_put_value_in_prev(head, current, mini, current_node)))
		return (free_and_null(&str), 0);
	return (free_and_null(&str), 1);
}

/*
**	Validates the token following the redirection operator at current,
**	then dispatches to uptade_unit_struct_redir with the matching
**	redirection type. Returns 1 on success, 0 on syntax error.
*/
int	parse_redirection_token(t_token *current, t_mini *mini, int cmdi)
{
	if (current->next->type == TOKEN_EOF)
	{
		print_error(ERR_REDIR);
		return (0);
	}
	if (current->next->type != TOKEN_WORD)
	{
		error_redir_message(current);
		return (0);
	}
	if (ft_strncmp(current->value, ">>", 2) == 0)
		return (uptade_unit_struct_redir(mini, current, APPEND, cmdi));
	else if (ft_strncmp(current->value, "<<", 2) == 0)
		return (uptade_unit_struct_redir(mini, current, HEREDOC, cmdi));
	else if (current->value[0] == '>')
		return (uptade_unit_struct_redir(mini, current, REDIR_OUT, cmdi));
	else if (current->value[0] == '<')
		return (uptade_unit_struct_redir(mini, current, REDIR_IN, cmdi));
	else
		return (0);
	return (1);
}
