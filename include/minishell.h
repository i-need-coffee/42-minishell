#ifndef MINISHELL_H
# define MINISHELL_H

/*
** ================================
**			LIBRARIES
** ================================
*/

# include <libft.h>
# include <errors.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
** ================================
**		ENUMS & STRUCTS
** ================================
*/

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_mini
{
	char	*input;
	t_token	*tokens;
}	t_mini;

/*
** ================================
**			FUNCTIONS
** ================================
*/

/* -- DEBUG -- */
void	print_tokens(t_token **root);

/* -- GENERAL -- */
void	cleanup_exit(t_mini *mini, int exit_code);
void	cleanup(t_mini *mini);
void	print_error(char *err_msg);
int		return_error(char *err_msg, int err_code);

/* -- TOKENIZATION -- */
void	tokenize_input(t_mini *mini);
void	free_tokens(t_token **root);
int		add_token(t_token **root, t_token_type type, char *value);
void	add_word_token(t_mini *mini, int *i);
int		has_unclosed_quotes(char *input);

#endif