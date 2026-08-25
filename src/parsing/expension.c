/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jturrel <jturrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 16:59:41 by jturrel           #+#    #+#             */
/*   Updated: 2026/08/25 17:00:41 by jturrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar(char *str, int i, t_mini *mini, char **b)
{
	char	*buffer;

	buffer = NULL;
	if (create_or_update_buffer(&buffer, str, i, i) == 0)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	i = expension(str, i, mini, &buffer);
	*b = ft_strdup(buffer);
	if (!*b)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
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
		return (0);
	return (1);
}

int	check_key(t_env *temp_env, char *key, int end, char **buffer)
{
	char	*tmp_buffer;

	tmp_buffer = (char *)malloc(ft_strlen(*buffer) + 1);
	if (!tmp_buffer)
		return (0);
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

int	handle_inter_mark(t_mini *mini, char **buffer)
{
	char	*tmp;

	if (g_sig != 0)
		mini->err_num = 128 + g_sig;
	tmp = ft_itoa(mini->err_num);
	if (!tmp)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	free_and_null(buffer);
	*buffer = ft_strdup(tmp);
	if (!*buffer)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	free(tmp);
	tmp = NULL;
	g_sig = 0;
	return (1);
}

int	expension(char *str, int i, t_mini *mini, char **buffer)
{
	int		end;
	char	*key;
	t_env	*temp_env;

	temp_env = mini->env;
	i++;
	end = i;
	if (str[end] == '?')
	{
		handle_inter_mark(mini, buffer);
		end++;
		return (end);
	}
	while (str[end] == '_' || ft_isalnum(str[end]))
		end++;
	key = ft_substr(str, i, end - i);
	if (!key)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	if (check_key(temp_env, key, end, buffer) == 0)
	{
		free_and_null(&key);
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	}
	free_and_null(&key);
	return (end);
}
