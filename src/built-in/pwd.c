#include "minishell.h"

int	pwd(void)
{
	size_t	size;
	char	*buffer;

	size = 1024;
	buffer = malloc(size * sizeof(char));
	while (!getcwd(buffer, size))
	{
		if (errno != ERANGE)
		{
			perror(ERR_PWD);
			free(buffer);
			return (1);
		}
		size *= 2;
		free(buffer);
		buffer = malloc(size * sizeof(char));
	}
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}
