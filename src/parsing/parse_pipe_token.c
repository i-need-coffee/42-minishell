#include "minishell.h"

int	parse_pipe_token(t_pipe_unit **unit, t_token *current, int *cmdi)
{
	if (current->prev == NULL || current->next == NULL)
	{
		ft_printf (ERR_UNEXPECTED_TOKEN_PIPE);
		return (-1);
	}
	if (current->prev->type != TOKEN_WORD || current->next->type != TOKEN_WORD)
	{
		ft_printf (ERR_UNEXPECTED_TOKEN_PIPE);
		return (-1);
	}
	create_or_update_unit_struct(unit, *cmdi, PIPE_OUT);
	(*cmdi)++;
	create_or_update_unit_struct(unit, *cmdi, PIPE_IN);
	return (0);
}
