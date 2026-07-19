#include "minishell.h"

// static int	internal_check_quote_sanity(char *str, int end, char c)
// {
// 	while (str[end] && str[end] != c)
// 		end++;
// 	if (str[end] != c)
// 		return (-1);
// 	return (end);
// }

void clean_str(char *str) {
	if (str) {
		ft_strlcpy(str, "", ft_strlen(str));
	}
}

int put_value_in_prev_args(t_pipe_unit *cnode, t_token *current, t_env *env) {
	int i;
	char *tmp;
	char *str;
	tmp = NULL;
	i = 0;
	str = current->value;
	while (str[i]) {
		i = add_arg(&str, i, cnode, env);
		if (i == -1)
			return (-1);
		while (str[i] == ' ')
			i++;
	}
	return (0);
}

void	create_redirection_node(t_pipe_unit **head,t_token *next, char* filename) {
	t_pipe_unit *tmp_unit;
	char *buffer;

	tmp_unit = *head;
	while (tmp_unit->next) {
		tmp_unit = tmp_unit->next;
	}
	tmp_unit->file = filename;
	buffer = ft_strtrim(next->value, " \t");
	free(next->value);
	next->value = NULL;
	next->value = buffer;
}

// int  handle_literal_argument(t_pipe_unit **unit, t_token *next) {
// 	int end;
// 	char    *buffer;
// 	char    *tmp;
// 	t_pipe_unit *tmp_unit;
//
// 	tmp_unit = *unit;
// 	while (tmp_unit->next)
// 		tmp_unit = tmp_unit->next;
// 	end = internal_check_quote_sanity(next->value, 1, '\"');
// 	if (end == -1 )
// 		return (-1);
// 	//TODO: gerer le cas ou != ' '. genre "infile".txt
// 	tmp_unit->file = ft_substr(next->value, 1, end - 1);
// 	buffer = ft_substr(next->value, end + 1, ft_strlen(next->value) - end);
// 	tmp = ft_strtrim(buffer, " ");
// 	free(next->value);
// 	free(buffer);
// 	next->value = tmp;
// 	return (0);
// }


// int handle_single_argument(t_pipe_unit **unit, t_token *next) {
// 	int end;
// 	char    *buffer;
// 	char    *tmp;
// 	t_pipe_unit *tmp_unit;
//
// 	tmp_unit = *unit;
// 	while (tmp_unit->next)
// 		tmp_unit = tmp_unit->next;
// 	end = 0;
// 	while (next->value[end] && next->value[end] != ' ')
// 		end++;
// 	//TODO: gerer le cas ou != ' '. genre "infile".txt
// 	tmp_unit->file = ft_substr(next->value, 0, end);
// 	buffer = ft_substr(next->value, end + 1, ft_strlen(next->value) - end);
// 	tmp = ft_strtrim(buffer, " ");
// 	free(next->value);
// 	free(buffer);
// 	next->value = tmp;
// 	return (0);
// }

