#include "minishell.h"

static void	swap_values_node(t_env *curr, t_env *next);
static void	join_and_print_node(t_mini *mini, t_env *node);

void	sort_env_nodes(t_env **root)
{
	t_env	*node;
	int		i;
	int		j;
	int		count;

	i = 0;
	count = count_env_nodes(*root);
	while (i < count - 1)
	{
		node = *root;
		j = 0;
		while (j < (count - i - 1))
		{
			if (node && node->next && ft_strcmp(node->key, node->next->key) > 0)
				swap_values_node(node, node->next);
			node = node->next;
			j++;
		}
		i++;
	}
}

void	print_env_nodes(t_mini *mini)
{
	t_env	*node;

	node = mini->env;
	while (node)
	{
		join_and_print_node(mini, node);
		node = node->next;
	}
}

static void	swap_values_node(t_env *curr, t_env *next)
{
	char	*temp;

	temp = curr->key;
	curr->key = next->key;
	next->key = temp;
	temp = curr->value;
	curr->value = next->value;
	next->value = temp;
}

static void	join_and_print_node(t_mini *mini, t_env *node)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(node->value, "\"");
	if (!temp1)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	temp2 = ft_strjoin("=\"", temp1);
	free_and_null(&temp1);
	if (!temp2)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	temp1 = ft_strjoin(node->key, temp2);
	free_and_null(&temp2);
	if (!temp1)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	temp2 = ft_strjoin("declare -x ", temp1);
	free_and_null(&temp1);
	if (!temp2)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	printf("%s\n", temp2);
	free_and_null(&temp2);
}
