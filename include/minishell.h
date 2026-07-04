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
# include <errno.h>
# include <fcntl.h>

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
	HEREDOC,
	PIPE_OUT,
	PIPE_IN
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
	t_token_segment	*segments;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe_unit
{
	t_unit_type			type;
	char				**args;
	char				*file;
	int					fd;
	int					cmd_index;
	struct s_pipe_unit	*next;
}	t_pipe_unit;

typedef struct s_mini
{
	char		*input;
	int			pipe_nb;
	int			cmd_nb;
	t_token		*tokens;
	t_env		*env;
	t_pipe_unit	*units;
	pid_t		*pids;
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
void			add_word_token(t_mini *mini, int *i);
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

/* -- EXECUTION --*/
int				execute_input(t_mini *mini);
int				execute_heredocs(t_mini *mini);
void			free_pipe_units(t_pipe_unit **root);
int				create_pipes(t_mini *mini);
int				open_files(t_pipe_unit *units, int i);
int				create_children(t_mini *mini);

#endif