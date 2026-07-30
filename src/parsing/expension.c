#include "minishell.h"

int	wrapper_handle_dollar(char **str, char **tmp, int *i, t_env *env) // handle error avant
{
	int	start;

	start = *i;
	*i = handle_dollar(*str, *(i), env, tmp);//message error handle
	if (*i == 0)
		return (0);
	*i = replace_str(str, *tmp, start, *(i)); //message error handle
	if (*i == 0)
		return (0);
	return (1);
}

int	handle_dollar(char *str, int i, t_env *env, char **b) //message error handle
{
	char	*buffer;

	buffer = NULL;
	if (create_or_update_buffer(&buffer, str, i, i) == 0)
		return (0);
	i = expension(str, i, env, &buffer);
	if (i == 0)
		return (0);
	*b = ft_strdup(buffer);
	if (!*b) {
		print_error(ERR_ALLOC);
		return (0);
	}
	free(buffer);
	buffer = NULL;
	return (i);
}

int	check_key(t_env *temp_env, char *key, int end, char **buffer)
{
	char	*tmp_buffer;

	tmp_buffer = (char *)malloc(ft_strlen(*buffer) + 1);
	if (!tmp_buffer) {
		print_error(ERR_ALLOC);
		return (0);
	}
	while (temp_env)
	{
		if (!ft_strncmp(key, temp_env->key, end))
		{
			ft_strlcpy(tmp_buffer, *buffer, (ft_strlen(*buffer) + 1));
			free(*buffer);
			*buffer = ft_strjoin(tmp_buffer, temp_env->value);
			free(key);
			free(tmp_buffer);
			if (!*buffer) {
				print_error(ERR_ALLOC);
				return (0);
			}
			return (end);
		}
		temp_env = temp_env->next;
	}
	free(tmp_buffer);
	return (1);
}

int	expension(char *str, int i, t_env *env, char **buffer) // message error handle
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
	if (!key) {
		print_error(ERR_ALLOC);
		return (0);
	}
	if (check_key(temp_env, key, end, buffer) == 0) // error message handle
		return (0);
	return (end);
}
