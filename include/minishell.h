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

extern int	g_sig;

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

typedef struct s_pipe_unit
{
	t_unit_type			type;
	t_list				*args;
	char				*file;
	int					fd;
	int					cmd_index;
	struct s_pipe_unit	*prev;
	struct s_pipe_unit	*next;
}	t_pipe_unit;

typedef struct s_mini
{
	char		*input;
	int			pipe_nb;
	int			err_num;
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
void			signal_config(int signb, void *handler);
void			handler_sigint(int signb);
void			handler_sigquit(int signb);
void			set_global_var(int signb);

/* -- ENVIRONEMENT --*/
t_env			**build_env(char **envp, t_env **env);
void			add_back(t_env **env, t_env *new);
t_env			*new_node(void);
int				strlen_key(char *envp);
void			free_env(t_env **root);

/* -- PARSING --*/
int				parse_tokens(t_mini *mini, t_pipe_unit **head);
int				parse_word_token(
					t_pipe_unit **head, t_token *tkn, t_env *env, int cmdi);
int				add_arg(char **str, int i, t_pipe_unit *unit, t_env *env);
int				expension(char *str, int i, t_env *env, char **buffer);
int				handle_quote(char *str, int i, t_env *env, char **b);
void			create_or_update_buffer(
					char **buffer, char *str, int start, int end);
void			create_or_update_lst(t_pipe_unit *unit, char *buffer);
int				check_quote_sanity(char *str, int end, char c);
t_pipe_unit		*create_or_update_unit_struct(
					t_pipe_unit **head, int cmdi, t_unit_type type);
int				handle_dollar(char *str, int i, t_env *env, char **b);
int				parse_pipe_token(
					t_pipe_unit **unit, t_token *current, int *cmdi);
int				parse_redirection_token(
					t_pipe_unit **unit, t_token *current, t_env *env);
void			clean_str(char *str);
int				put_value_in_prev_args(
					t_pipe_unit *cnode, t_token *current, t_env *env);
int				replace_str(
					char **str, char *second_part,
					int replace_start, int replace_end );
void			create_redirection_node(
					t_pipe_unit **head, t_token *next, char *filename);
t_pipe_unit		*new_unit_node(int cmdi, t_unit_type type);
void			wrapper_handle_dollar(
					char **str, char **tmp, int *i, t_env *env);
int				wrapper_handle_quote(
					char *str, int *index, t_env *env, char **tmp);

#endif