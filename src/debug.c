#include "minishell.h"

void	print_tokens(t_token **root)
{
	t_token			*curr;
	int				i;

	curr = *root;
	i = 0;
	ft_printf("-- TOKENS START --\n");
	while (curr->type != TOKEN_EOF)
	{
		ft_printf("\nTOKEN[%d]\n", i);
		ft_printf("  TYPE: %d\n", curr->type);
		ft_printf("  VALUE: %s\n", curr->value);
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
