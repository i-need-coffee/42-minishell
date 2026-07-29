#include "minishell.h"

int	parse_pipe_token(t_pipe_unit **unit, t_token *current, int *cmdi)
{
	if (current->prev == NULL || current->next == NULL)
	{
		print_error(ERR_SYNTAX_PIPE);
		return (0);
	}
	if (current->prev->type != TOKEN_WORD || current->next->type != TOKEN_WORD)
	{
		print_error(ERR_SYNTAX_PIPE);
		return (0);
	}
	if (!(create_or_update_unit_struct(unit, *cmdi, PIPE_OUT)))
		return (0);// mess error handle
	(*cmdi)++;
	if (!(create_or_update_unit_struct(unit, *cmdi, PIPE_IN)))
			return (0);// mess error handle
	return (1);
}
