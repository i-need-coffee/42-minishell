#include "minishell.h"

void	free_tokens(t_token **root)
{
	t_token	*curr;
	t_token	*temp;

	curr = *root;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	*root = NULL;
}

void	print_tokens(t_token *token)
{
	ft_printf("-- START TOKENS --\n");
	while (token->type != TOKEN_EOF)
	{
		printf("type: %d, value: %s\n", token->type, token->value);
		token = token->next;
	}
	ft_printf("-- END TOKENS --\n");
}
