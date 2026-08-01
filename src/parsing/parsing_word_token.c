#include "minishell.h"

int	parse_word_token(t_pipe_unit **head, t_token *current, t_env *env, int cmdi)
{
	int			i;
	int			start;
	t_pipe_unit	*new_token;
	char		*str;

	str = current->value;
	if (!(create_or_update_unit_struct(head, cmdi, CMD)))
		return (0);
	new_token = *head;
	while (new_token->next)
		new_token = new_token->next;
	i = 0;
	start = i;
	while (str[i])
	{
		i = add_arg(&str, i, new_token, env);
		if (i == -1)
			return (0);
		while (str[i] == ' ')
			i++;
	}
	return (1);
}
