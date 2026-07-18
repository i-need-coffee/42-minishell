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

void	print_perror(char *err_msg, int errnum)
{
	write(2, err_msg, ft_strlen(err_msg));
	write(2, ": ", 2);
	write(2, strerror(errnum), ft_strlen(strerror(errnum)));
	write(2, "\n", 1);
}
