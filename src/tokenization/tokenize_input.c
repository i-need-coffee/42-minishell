#include "minishell.h"

static int	add_token(t_token **root, t_token_type type, char *value);

void	tokenize_input(t_mini *mini)
{
	add_token(&mini->tokens, TOKEN_WORD, "grep");
	add_token(&mini->tokens, TOKEN_WORD, "hello");
	add_token(&mini->tokens, TOKEN_PIPE, "|");
	add_token(&mini->tokens, TOKEN_WORD, "wc");
	add_token(&mini->tokens, TOKEN_WORD, "-l");
	add_token(&mini->tokens, TOKEN_REDIR_IN, "<");
	add_token(&mini->tokens, TOKEN_REDIR_OUT, ">");
	add_token(&mini->tokens, TOKEN_APPEND, ">>");
	add_token(&mini->tokens, TOKEN_HEREDOC, "<<");
	add_token(&mini->tokens, TOKEN_EOF, NULL);
}

static int	add_token(t_token **root, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*curr;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->type = type;
	new_token->value = value;
	if (!*root)
	{
		*root = new_token;
		return (1);
	}
	curr = *root;
	while (curr->next)
		curr = curr->next;
	curr->next = new_token;
	new_token->prev = curr;
	return (1);
}
