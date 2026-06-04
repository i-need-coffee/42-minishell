#include "minishell.h"

void	print_error(char *err_msg)
{
	write(2, "error: ", 7);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
}

void	print_error_and_exit(t_mini *mini, char *err_msg, int exit_code)
{
	print_error(err_msg);
	cleanup_exit(mini, exit_code);
}
