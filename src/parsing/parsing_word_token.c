#include "minishell.h"

int	parse_word_token(t_pipe_unit **head, t_token *current, t_mini *mini,
		int cmdi)
{
	int			i;
	t_pipe_unit	*new_token;
	char		*str;

	str = ft_strdup(current->value);
	if (!str)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	if (!(create_or_update_unit_struct(head, cmdi, CMD)))
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	new_token = *head;
	while (new_token->next)
		new_token = new_token->next;
	i = 0;
	while (str[i])
	{
		i = add_arg(&str, i, new_token, mini);
		if (i == -1)
			return (0);
		while (str[i] == ' ')
			i++;
	}
	free_and_null(&str);
	return (1);
}
