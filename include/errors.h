#ifndef ERRORS_H
# define ERRORS_H

# define ERR_ALLOC			"minishell: memory allocation failed"
# define ERR_QUOTES			"minishell: incorrect syntax: unclosed quotes"
# define ERR_SIGACTION		"minishell: sigaction failed"
# define ERR_PIPE			"minishell: pipe failed"
# define ERR_FORK			"minishell: fork failed"
# define ERR_DUP2			"minishell: dup2 failed"
# define ERR_DUP			"minishell: dup failed"
# define ERR_WAITPID		"minishell: waitpid failed"
# define ERR_WRITE			"minishell: write failed"
# define ERR_RESTORE_FDS	"minishell: impossible to restore original STDIN and STDOUT"
# define ERR_PWD			"minishell: pwd"

#endif