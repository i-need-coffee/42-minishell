#include "minishell.h"

void	wrapper_handle_dollar(char **str, char **tmp, int *i, t_env *env)
{
	int	start;

	start = *i;
	*i = handle_dollar(*str, *(i), env, tmp);
	*i = replace_str(str, *tmp, start, *(i));
}

int	handle_dollar(char *str, int i, t_env *env, char **b)
{
	char	*buffer;

	buffer = NULL;
	create_or_update_buffer(&buffer, str, i, i);
	i = expension(str, i, env, &buffer);
	*b = ft_strdup(buffer);
	free(buffer);
	buffer = NULL;
	return (i);
}

int	check_key(t_env *temp_env, char *key, int end, char **buffer)
{
	char	*tmp_buffer;

	tmp_buffer = (char *)malloc(ft_strlen(*buffer) + 1);
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
	free(tmp_buffer);
	return (-1);
}

int	expension(char *str, int i, t_env *env, char **buffer)
{
	int		end;
	char	*key;
	t_env	*temp_env;

	temp_env = env;
	i++;
	end = i;
	while (str[end] == '_' || ft_isalnum(str[end]))
		end++;
	key = ft_substr(str, i, end - i);
	if (check_key(temp_env, key, end, buffer) != -1)
		return (end);
	free(key);
	return (end);
}
