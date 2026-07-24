#include "minishell.h"

static void	sort_nodes(t_env **root);
static void	swap_nodes(t_env *curr, t_env *next);
static void	print_nodes(t_mini *mini);

int	export(t_mini *mini, char **args)
{
	int	arg_count;

	arg_count = count_args(args);
	if (arg_count == 1)
	{
		sort_nodes(&mini->env);
		print_nodes(mini);
	}
	return (0);
}

static void	sort_nodes(t_env **root)
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
				swap_nodes(node, node->next);
			node = node->next;
			j++;
		}
		i++;
	}
}

static void	swap_nodes(t_env *curr, t_env *next)
{
	char	*temp;

	temp = curr->key;
	curr->key = next->key;
	next->key = temp;
	temp = curr->value;
	curr->value = next->value;
	next->value = temp;
}

static void	print_nodes(t_mini *mini)
{
	char	*temp1;
	char	*temp2;

	while (mini->env)
	{
		temp1 = ft_strjoin(mini->env->value, "\"");
		if (!temp1)
			print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
		temp2 = ft_strjoin("=\"", temp1);
		free_and_null(&temp1);
		if (!temp2)
			print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
		temp1 = ft_strjoin(mini->env->key, temp2);
		free_and_null(&temp2);
		if (!temp1)
			print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
		temp2 = ft_strjoin("declare -x ", temp1);
		free_and_null(&temp1);
		if (!temp2)
			print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
		printf("%s\n", temp2);
		free_and_null(&temp2);
		mini->env = mini->env->next;
	}
}
