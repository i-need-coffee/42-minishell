#include "minishell.h"

void	print_tokens(t_token **root)
{
	t_token			*curr;
	t_token_segment	*seg;
	int				i;

	curr = *root;
	i = 0;
	ft_printf("-- TOKENS START --\n");
	while (curr->type != TOKEN_EOF)
	{
		ft_printf("\nTOKEN[%d]\n", i);
		ft_printf("  TYPE: %d\n", curr->type);
		if (curr->segments)
		{
			seg = curr->segments;
			while (seg)
			{
				ft_printf("  SEG[quote: %d, value: %s]\n",
					seg->quote_type, seg->value);
				seg = seg->next;
			}
		}
		i++;
		curr = curr->next;
	}
	ft_printf("\n-- TOKENS END --\n");
}

void	print_node_env(t_env *node)
{
	while (node)
	{
		ft_printf("key: %s, value: %s\n", node->key, node->value);
		node = node->next;
	}
}
