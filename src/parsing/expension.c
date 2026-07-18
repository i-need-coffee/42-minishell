#include "minishell.h"

int	handle_dollar(char *str, int i, t_env *env, t_pipe_unit *new_token)
{
	char *buffer;
	char *tmp;

	tmp = NULL;
	buffer = NULL;
	create_or_update_buffer(&buffer, str, i, i);
	i = expension(str, i, env, &buffer);
	tmp = ft_strdup(buffer);
	free(buffer);
	buffer = NULL;
	create_or_update_lst(new_token, tmp);
	return (i);
}

int	expension(char *str, int i, t_env *env, char **buffer)
{
	int		end;
	char	*key;
	char	*tmp_buffer;
	t_env	*temp_env;

	temp_env = env;
	i++;
	end = i;
	tmp_buffer = (char *)malloc(ft_strlen(*buffer) + 1);
	while (ft_isalnum(str[end]))
		end++;
	key = ft_substr(str, i, end - i);
	while (temp_env)
	{
		if (!ft_strncmp(key, temp_env->key, end))
		{
			ft_strlcpy(tmp_buffer, *buffer, (ft_strlen(*buffer) + 1));
			free(*buffer);
			*buffer = ft_strjoin(tmp_buffer, temp_env->value);
			free(key);
			free(tmp_buffer);
			return (end);
		}
		temp_env = temp_env->next;
	}
	free(key);
	free(tmp_buffer);
	return (end);
}
