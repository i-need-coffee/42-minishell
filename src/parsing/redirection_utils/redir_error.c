#include "minishell.h"

void	error_redir_message(t_token *current)
{
	if (current->next->type == TOKEN_REDIR_OUT )
		print_error(ERR_REDIR_OUT);
	else if (current->next->type == TOKEN_REDIR_IN)
		print_error(ERR_REDIR_IN);
	else if (current->next->type == TOKEN_APPEND)
		print_error(ERR_APPEND);
	else if (current->next->type == TOKEN_HEREDOC)
		print_error(ERR_HEREDOC);
}