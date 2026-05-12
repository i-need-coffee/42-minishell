#include "minishell.h"

void	print_error(char *err_msg)
{
	write(2, "error: ", 7);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
}

int	return_error(char *err_msg, int err_code)
{
	print_error(err_msg);
	return (err_code);
}
