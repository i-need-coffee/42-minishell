#include "minishell.h"

void	print_tokens(t_token **root)
{
	t_token			*curr;
	t_token_segment	*seg;

	curr = *root;
	ft_printf("-- TOKENS START --\n");
	while (curr->type != TOKEN_EOF)
	{
		ft_printf("TYPE: %d\n", curr->type);
		if (curr->segments)
		{
			seg = curr->segments;
			while (seg)
			{
				ft_printf("  SEG[quote=%d, value=%s]\n",
					seg->quote_type, seg->value);
				seg = seg->next;
			}
		}
		curr = curr->next;
	}
	ft_printf("-- TOKENS END --\n");
}
