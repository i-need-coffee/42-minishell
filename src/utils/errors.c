#include "minishell.h"

/*
**	Prints an error message to stderr.
*/
void	print_error(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
}

/*
**	Prints an error message to stderr, then frees everything and exits.
*/
void	print_error_and_exit(t_mini *mini, char *err_msg, int exit_code)
{
	print_error(err_msg);
	cleanup_exit(mini, exit_code);
}

void	ft_abort(char *msg)
{
	perror(msg);
	exit(1);
}

/*
**	Prints "minishell: err_msg: <strerror(errnum)>" to stderr, mimicking
**	perror() but with a custom prefix instead of the program name.
*/
void	print_perror(char *err_msg, int errnum)
{
	write(2, "minishell: ", 11);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, ": ", 2);
	write(2, strerror(errnum), ft_strlen(strerror(errnum)));
	write(2, "\n", 1);
}

void	print_error3(char *start, char *middle, char *end)
{
	write(2, start, ft_strlen(start));
	write(2, ": ", 2);
	write(2, middle, ft_strlen(middle));
	write(2, ": ", 2);
	write(2, end, ft_strlen(end));
	write(2, "\n", 1);
}
