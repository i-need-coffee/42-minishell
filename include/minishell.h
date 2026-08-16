#ifndef MINISHELL_H
# define MINISHELL_H

/*
** ================================
**			LIBRARIES
** ================================
*/

# include <errno.h>
# include <errors.h>
# include <fcntl.h>
# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>

/*
** ================================
**		ENUMS & STRUCTS
** ================================
*/

extern int				g_sig;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}						t_token_type;

typedef enum e_unit_type
{
	CMD,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	PIPE_OUT,
	PIPE_IN
}						t_unit_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*prev;
	struct s_env		*next;
}						t_env;

typedef struct s_pipe_unit
{
	t_unit_type			type;
	char				**args;
	char				*file;
	int					quoted_hd;
	int					fd;
	int					cmd_index;
	struct s_pipe_unit	*prev;
	struct s_pipe_unit	*next;
}						t_pipe_unit;

typedef struct s_mini
{
	char				*input;
	int					pipe_nb;
	int					err_num;
	int					cmd_nb;
	int					saved_stdin;
	int					saved_stdout;
	t_token				*tokens;
	t_env				*env;
	char				**envp;
	t_pipe_unit			*units;
	pid_t				*pids;
}						t_mini;

/*
** ================================
**			FUNCTIONS
** ================================
*/

/* -- DEBUG -- */
void					print_tokens(t_token **root);
void					print_node_env(t_env *node);

/* -- UTILS -- */
void					cleanup_exit(t_mini *mini, int exit_code);
void					cleanup(t_mini *mini);
void					print_error(char *err_msg);
int						has_unclosed_quotes(char *input);
void					print_error_and_exit(t_mini *mini, char *err_msg,
							int exit_code);
void					free_everthing(t_mini *mini);
void					ft_abort(char *msg);
void					print_error3(char *start, char *middle, char *end);

/* -- TOKENIZATION -- */
void					tokenize_input(t_mini *mini);
int						add_token(t_token **root, t_token_type type,
							char *value);
void					add_word_token(t_mini **mini, int *i);
void					free_tokens(t_token **root);

/* -- SIGNALS -- */
void					signal_config(int signb, void *handler);
void					handler_sigint(int signb);
void					handler_sigquit(int signb);
void					set_global_var(int signb);

/* -- ENVIRONEMENT --*/
int						build_env(char **envp, t_env **env);
void					add_back(t_env **env, t_env *new);
t_env					*new_node(void);
int						strlen_key(char *envp);
void					free_env(t_env **root);
char					*get_value_with_key(t_env *env, char *key);
int						count_env_nodes(t_env *env);
t_env					*get_env_node_with_key(t_env **root, char *key);
int						add_base_env(t_env **env);
t_env					*create_env_node(char *envp_node);

/* -- EXECUTION --*/
void					execute_input(t_mini *mini);
int						execute_heredocs(t_mini *mini);
void					free_pipe_units(t_pipe_unit **root);
int						create_pipes(t_mini *mini);
int						open_files(t_pipe_unit *units, int i);
int						create_children(t_mini *mini);
int						execute_cmd(t_mini *mini, t_pipe_unit *cmd);
void					wait_children(t_mini *mini);
void					close_all_fds(t_pipe_unit *units);
t_pipe_unit				*get_cmd_unit(t_pipe_unit *units, int i);
char					**build_envp_tab(t_env *env);
int						dup_pipes(t_pipe_unit *units, int i);
int						dup_redirects(t_pipe_unit *units, int i);
int						dup_saved_fds(int *saved_stdin, int *saved_stdout);
int						restore_saved_stdin(t_mini *mini);
int						restore_saved_stdout(t_mini *mini);

/* -- BUILT-IN --*/
int						is_built_in(t_pipe_unit *cmd);
int						execute_built_in(t_mini *mini, t_pipe_unit *cmd);
int						echo(char **args);
int						pwd(void);
int						cd(t_env *env, char **args);
int						count_args(char **args);
int						env(char **envp, char **args);
int						unset(t_env **root, char **args);
int						export(t_env *env, char **args);
void					sort_env_nodes(t_env **root);
int						print_env_nodes(t_env **root);
char					*get_curr_dir(void);
int						exit_minishell(t_mini *mini, char **args);

/* -- PARSING --*/
int						parse_tokens(t_mini *mini, t_pipe_unit **head);
int						parse_word_token(t_pipe_unit **head, t_token *tkn,
							t_mini *mini, int cmdi);
int						add_arg(char **str, int i, t_pipe_unit *unit,
							t_mini *mini);
int						expension(char *str, int i, t_mini *mini,
							char **buffer);
int						handle_quote(char *str, int i, t_mini *mini, char **b);
int						create_or_update_buffer(char **buffer, char *str,
							int start, int end);
int						create_or_update_args(t_pipe_unit *unit, char *buffer);
int						check_quote_sanity(char *str, int end, char c);
int						create_or_update_unit_struct(t_pipe_unit **head,
							int cmdi, t_unit_type type);
int						handle_dollar(char *str, int i, t_mini *mini, char **b);
int						parse_pipe_token(t_pipe_unit **unit, t_token *current,
							int *cmdi, t_mini *mini);
int						parse_redirection_token(t_token *current, t_mini *mini, int cmdi);
void					clean_str(char *str);
int						put_value_in_prev_args(t_pipe_unit *cnode,
							t_token *current, t_mini *mini);
int						replace_str(char **str, char *second_part,
							int replace_start, int replace_end);
int						create_redirection_node(t_pipe_unit **head,
							t_token *next, char *filename);
t_pipe_unit				*new_unit_node(int cmdi, t_unit_type type);
int						wrapper_handle_dollar(char **str, int *i, t_mini *mini);
int						wrapper_handle_quote(char *str, int *index, t_mini *mini,
							char **tmp);
int						wrapper_update_buffer(char *buffer, char *str,
							int start, int buff_len);
int						wrapper_put_value_in_prev(t_pipe_unit **head,
							t_token *current, t_mini *mini,
							t_pipe_unit *current_node);
int						wrapper_coub(char **quote_buffer, char *str, int start,
							int i);
int						check_if_expension(char *str, int *i);
int						quoted_heredoc(t_mini *mini, t_token *current);
#endif