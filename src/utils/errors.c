#include "minishell.h"

/*
**	Prints an error message to stderr.
*/
void	print_error(char *err_msg)
{
	write(2, "error: ", 7);
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
