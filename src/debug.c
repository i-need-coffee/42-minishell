#include "minishell.h"

void	print_tokens(t_token **root)
{
	t_token	*curr;

	curr = *root;
	ft_printf("-- TOKENS START --\n");
	while (curr->type != TOKEN_EOF)
	{
		ft_printf("TYPE: %d, VALUE: %s, EXPANDS: %d\n",
			curr->type, curr->value, curr->expands);
		curr = curr->next;
	}
	ft_printf("-- TOKENS END --\n");
}
