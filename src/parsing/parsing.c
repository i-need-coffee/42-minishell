#include "minishell.h"

// This function parse the types of mini(WORD, PIPE, etc)
// and print unit->args nodes for debugging

int	parse_tokens_word_or_pipe(t_mini *mini, t_token *current, int *cmdi,
		t_pipe_unit **unit)
{
	if (current->type == TOKEN_WORD)
	{
		if (parse_word_token(unit, current, mini->env, *cmdi) < 0)
			return (-1);
	}
	else if (current->type == TOKEN_PIPE)
	{
		if (parse_pipe_token(unit, current, cmdi))
			return (-1);
	}
	return (0);
}

int	parse_tokens_redirection(t_mini *mini, t_token *current, t_pipe_unit **unit)
{
	if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
		|| current->type == TOKEN_APPEND || current->type == TOKEN_HEREDOC)
	{
		if (parse_redirection_token(unit, current, mini->env))
			return (-1);
	}
	return (0);
}

int	parse_tokens(t_mini *mini, t_pipe_unit **unit)
{
	t_token	*current;
	int		cmdi;

	cmdi = 0;
	current = mini->tokens;
	while (current->type != TOKEN_EOF)
	{
		if (ft_strlen(current->value) == 0)
		{
			current = current->next;
			continue ;
		}
		else if (parse_tokens_word_or_pipe(mini, current, &cmdi, unit))
			return (-1);
		else if (parse_tokens_redirection(mini, current, unit))
			return (-1);
		if (*unit == NULL)
			return (-1); // todo: handle error
		current = current->next;
	}
	if (*unit && (*unit)->args)
		ft_lstiter((*unit)->args, &print_lst);
	return (0);
}
