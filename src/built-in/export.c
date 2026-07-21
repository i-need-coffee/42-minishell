#include "minishell.h"

static void	sort_nodes(t_env **root);
static void	swap_nodes(t_env **root, t_env *curr, t_env *next);
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

	node = *root;
	count = count_env_nodes(node);
	i = 0;
	while (i < (count - 1))
	{
		j = 0;
		while (j < (count - i - 1))
		{
			if (node->next && node->key > node->next->key)
				swap_nodes(root, node, node->next);
			j++;
		}
		i++;
		node = node->next;
	}
}

static void	swap_nodes(t_env **root, t_env *curr, t_env *next)
{
	if (curr == *root)
	{
		curr->prev = next;
		curr->next = next->next;
		next->prev = NULL;
		next->next = curr;
		next = *root;
	}
	else
	{
		curr->prev = next;
		curr->next = next->next;
		next->prev = curr->prev;
		next->next = curr;
	}
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
