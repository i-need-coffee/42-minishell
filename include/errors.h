#ifndef ERRORS_H
# define ERRORS_H

# define ERR_UNEXPECTED_TOKEN_PIPE "minishell: syntax error near unexpected token `|'\n"
# define ERR_SYNTAX_TOKEN_REDIRECTION "minishell: syntax error near unexpected token `newline'\n"
# define ERR_ALLOC		"minishell: memory allocation failed\n"
# define ERR_QUOTES		"minishell: incorrect syntax, unclosed quotes\n"
# define ERR_SIGACTION	"minishell: sigaction failed\n"
#endif