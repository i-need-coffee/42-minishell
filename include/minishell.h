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
# include <signal.h>
# include <stdio.h>

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
	TOKEN_EOF
}	t_token_type;

typedef enum e_quote_type
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quote_type;

typedef struct s_token_segment
{
	t_quote_type			quote_type;
	char					*value;
	struct s_token_segment	*next;
}	t_token_segment;

typedef struct s_token
{
	t_token_type	type;
	t_token_segment	*segments;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_mini
{
	char	*input;
	t_token	*tokens;
}	t_mini;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env *next;
}	t_env;

/*
** ================================
**			FUNCTIONS
** ================================
*/

/* -- DEBUG -- */
void			print_tokens(t_token **root);

/* -- UTILS -- */
void			cleanup_exit(t_mini *mini, int exit_code);
void			cleanup(t_mini *mini);
void			print_error(char *err_msg);
int				has_unclosed_quotes(char *input);
void			print_error_and_exit(
					t_mini *mini, char *err_msg, int exit_code);

/* -- TOKENIZATION -- */
void			tokenize_input(t_mini *mini);
t_token_segment	*generate_segments(char *value);
int				add_token(t_token **root, t_token_type type, char *value);
void			add_word_token(t_mini *mini, int *i);
void			free_tokens(t_token **root);
void			free_segments(t_token_segment **root);

/* -- SIGNALS -- */
void	signal_config_sigquit(int signb, void *handler_sigquit);
void	signal_config_sigint(int signb, void *handler_sigint);
void	handler_sigint(int signb);
void	handler_sigquit(int signb);

/* -- ENVIRONEMENT --*/
t_env   **build_env(char **envp, t_env **env);
void print_node_env(t_env *node);
//int get_key_value_into_node(char *env_line, char *key_buf, char *value_buf, t_env *node);
void	add_back(t_env **env, t_env *new);
t_env	*new_node(void);
int strlen_key(char *envp);

#endif