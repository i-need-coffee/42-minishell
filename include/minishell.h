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
# include "/usr/local/Cellar/readline/8.3.3/include/readline/readline.h"

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

typedef enum e_unit_type
{
	CMD,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_unit_type;

typedef struct s_token_segment
{
	t_quote_type			quote_type;
	char					*value;
	struct s_token_segment	*next;
}	t_token_segment;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	// t_token_segment	*segments;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_args
{
	char *arg;
	t_args *next;
} t_args;

typedef struct s_pipe_unit
{
	t_unit_type			type;
	t_args				*args;
	char				*file;
	int					fd; // laisse a -1
	int					cmd_index; // most important MTF
	struct s_pipe_unit	*next;
}	t_pipe_unit;

typedef struct s_mini
{
	char		*input;
	int			pipe_nb; //pipe nb a incrementer.
	t_token		*tokens;
	t_env		*env;
	t_pipe_unit	*units;
}	t_mini;

/*
** ================================
**			FUNCTIONS
** ================================
*/

/* -- DEBUG -- */
void			print_tokens(t_token **root);
void			print_node_env(t_env *node);

/* -- UTILS -- */
void			cleanup_exit(t_mini *mini, int exit_code);
void			cleanup(t_mini *mini);
void			print_error(char *err_msg);
int				has_unclosed_quotes(char *input);
void			print_error_and_exit(
					t_mini *mini, char *err_msg, int exit_code);
void			free_everthing(t_mini *mini);

/* -- TOKENIZATION -- */
void			tokenize_input(t_mini *mini);
t_token_segment	*generate_segments(char *value);
int				add_token(t_token **root, t_token_type type, char *value);
void			add_word_token(t_mini **mini, int *i);
void			free_tokens(t_token **root);
void			free_segments(t_token_segment **root);

/* -- SIGNALS -- */
void			signal_config_sigquit(int signb, void *handler_sigquit);
void			signal_config_sigint(int signb, void *handler_sigint);
void			handler_sigint(int signb);
void			handler_sigquit(int signb);

/* -- ENVIRONEMENT --*/
t_env			**build_env(char **envp, t_env **env);
void			add_back(t_env **env, t_env *new);
t_env			*new_node(void);
int				strlen_key(char *envp);
void			free_env(t_env **root);

void	parse_tokens(t_mini *mini);

#endif