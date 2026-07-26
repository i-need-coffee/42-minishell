#include "minishell.h"

/*
**	Prints the current working directory, growing the buffer as needed
**	if it's too small.
*/
int	pwd(void)
{
	size_t	size;
	char	*buffer;

	size = 1024;
	buffer = malloc(size * sizeof(char));
	if (!buffer)
		return (perror(ERR_PWD), 1);
	while (!getcwd(buffer, size))
	{
		if (errno != ERANGE)
			return (perror(ERR_PWD), free(buffer), 1);
		size += 1024;
		free(buffer);
		buffer = malloc(size * sizeof(char));
		if (!buffer)
			return (perror(ERR_PWD), 1);
	}
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}
