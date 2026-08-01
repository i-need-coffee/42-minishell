#include "minishell.h"

/*
**	Returns the current working directory in a malloc'd buffer,
**	growing the buffer and retrying if it's too small.
*/
char	*get_curr_dir(void)
{
	size_t	size;
	char	*buffer;

	size = 1024;
	buffer = malloc(size * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!getcwd(buffer, size))
	{
		if (errno != ERANGE)
			return (free(buffer), NULL);
		size += 1024;
		free(buffer);
		buffer = malloc(size * sizeof(char));
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

/*
**	Prints the current working directory, growing the buffer as needed
**	if it's too small.
*/
int	pwd(void)
{
	char	*buffer;

	buffer = get_curr_dir();
	if (!buffer)
	{
		perror(ERR_PWD);
		return (1);
	}
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}
