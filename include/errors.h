#ifndef ERRORS_H
# define ERRORS_H

# define ERR_ALLOC			"minishell: cannot allocate memory"
# define ERR_QUOTES			"minishell: incorrect syntax: unclosed quotes"
# define ERR_SIGACTION		"minishell: sigaction failed"
# define ERR_PIPE			"minishell: pipe"
# define ERR_FORK			"minishell: fork"
# define ERR_DUP2			"minishell: dup2"
# define ERR_DUP			"minishell: dup"
# define ERR_WAITPID		"minishell: waitpid"
# define ERR_WRITE			"minishell: write"
# define ERR_RESTORE_FDS	"minishell: impossible to restore original STDIN and STDOUT"
# define ERR_PWD			"minishell: pwd"
# define ERR_ECHO			"minishell: echo"
# define ERR_CD				"minishell: cd"
# define ERR_CD_ARGS_NUM	"minishell: cd: too many arguments"
# define ERR_CD_NO_HOME		"minishell: cd: HOME not set"
# define ERR_ENV_ARGS_NUM	"minishell: env: too many arguments"
# define ERR_ALLOC_EXPORT	"minishell: export: cannot allocate memory"

#endif