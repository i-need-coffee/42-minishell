#include "minishell.h"

int	wrapper_handle_dollar(char **str, int *i, t_env *env)
{
	int		start;
	char	*tmp;

	start = *i;
	*i = handle_dollar(*str, *(i), env, &tmp);
	if (*i == 0)
		return (0);
	*i = replace_str(str, tmp, start, *(i));
	if (*i == 0)
		return (0);
	free(tmp);
	tmp = NULL;
	return (1);
}

int	handle_dollar(char *str, int i, t_env *env, char **b)
{
	char	*buffer;

	buffer = NULL;
	if (create_or_update_buffer(&buffer, str, i, i) == 0)
		return (0);
	i = expension(str, i, env, &buffer);
	if (i == 0)
		return (0);
	*b = ft_strdup(buffer);
	if (!*b)
	{
		print_error(ERR_ALLOC);
		return (0);
	}
	free(buffer);
	buffer = NULL;
	return (i);
}

int	cmp_key(char **buffer, char *tmp_buffer, t_env *temp_env)
{
	ft_strlcpy(tmp_buffer, *buffer, (ft_strlen(*buffer) + 1));
	free(*buffer);
	*buffer = NULL;
	*buffer = ft_strjoin(tmp_buffer, temp_env->value);
	free(tmp_buffer);
	tmp_buffer = NULL;
	if (!*buffer)
	{
		print_error(ERR_ALLOC);
		return (0);
	}
	return (1);
}

int	check_key(t_env *temp_env, char *key, int end, char **buffer)
{
	char	*tmp_buffer;

	tmp_buffer = (char *)malloc(ft_strlen(*buffer) + 1);
	if (!tmp_buffer)
	{
		print_error(ERR_ALLOC);
		return (0);
	}
	while (temp_env)
	{
		if (!ft_strncmp(key, temp_env->key, end))
		{
			if (!(cmp_key(buffer, tmp_buffer, temp_env)))
				return (0);
			return (end);
		}
		temp_env = temp_env->next;
	}
	free(tmp_buffer);
	tmp_buffer = NULL;
	return (1);
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
	if (!key)
	{
		print_error(ERR_ALLOC);
		return (0);
	}
	if (check_key(temp_env, key, end, buffer) == 0)
		return (free_and_null(&key), 0);
	free_and_null(&key);
	return (end);
}
