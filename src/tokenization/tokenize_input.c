#include "minishell.h"

static void	add_pipe_token(t_mini *mini, int *i);
static void	add_redir_token(t_mini *mini, char c, int *i);
static void	add_append_token(t_mini *mini, int *i);
static void	add_heredoc_token(t_mini *mini, int *i);

void	tokenize_input(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->input[i])
	{
		if (ft_isspace(mini->input[i]))
			i++;
		else if (mini->input[i] == '|')
			add_pipe_token(mini, &i);
		else if (mini->input[i] == '<' && mini->input[i + 1] != '<')
			add_redir_token(mini, '<', &i);
		else if (mini->input[i] == '>' && mini->input[i + 1] != '>')
			add_redir_token(mini, '>', &i);
		else if (mini->input[i] == '>' && mini->input[i + 1] == '>')
			add_append_token(mini, &i);
		else if (mini->input[i] == '<' && mini->input[i + 1] == '<')
			add_heredoc_token(mini, &i);
		else
			add_word_token(mini, &i);
	}
	if (!add_token(&mini->tokens, TOKEN_EOF, NO_QUOTES, NULL))
		cleanup_exit(mini, EXIT_FAILURE);
}

static void	add_pipe_token(t_mini *mini, int *i)
{
	if (!add_token(&mini->tokens, TOKEN_PIPE, NO_QUOTES, "|"))
		cleanup_exit(mini, EXIT_FAILURE);
	(*i)++;
}

static void	add_redir_token(t_mini *mini, char c, int *i)
{
	if (c == '<')
	{
		if (!add_token(&mini->tokens, TOKEN_REDIR_IN, NO_QUOTES, "<"))
			cleanup_exit(mini, EXIT_FAILURE);
	}
	else if (c == '>')
	{
		if (!add_token(&mini->tokens, TOKEN_REDIR_OUT, NO_QUOTES, ">"))
			cleanup_exit(mini, EXIT_FAILURE);
	}
	else
		return ;
	(*i)++;
}

static void	add_append_token(t_mini *mini, int *i)
{
	if (!add_token(&mini->tokens, TOKEN_APPEND, NO_QUOTES, ">>"))
		cleanup_exit(mini, EXIT_FAILURE);
	(*i) += 2;
}

static void	add_heredoc_token(t_mini *mini, int *i)
{
	if (!add_token(&mini->tokens, TOKEN_HEREDOC, NO_QUOTES, "<<"))
		cleanup_exit(mini, EXIT_FAILURE);
	(*i) += 2;
}
