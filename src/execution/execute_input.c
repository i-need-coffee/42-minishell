#include "minishell.h"

static char	**build_envp_tab(t_env *env);

void	init_data(t_mini *mini)
{
	// < infile cat | cat > outfile

	// ── CMD 0 : < infile cat | ────────────────────────────────────────────
	t_pipe_unit *u1 = calloc(1, sizeof(t_pipe_unit));
	u1->type = HEREDOC;
	u1->file = ft_strdup("EOF");
	u1->fd = -1;
	u1->cmd_index = 0;

	t_pipe_unit *u2 = calloc(1, sizeof(t_pipe_unit));
	u2->type = CMD;
	u2->args = malloc(2 * sizeof(char *));
	u2->args[0] = ft_strdup("cat");
	u2->args[1] = NULL;
	u2->fd = -1;
	u2->cmd_index = 0;

	t_pipe_unit *u3 = calloc(1, sizeof(t_pipe_unit));
	u3->type = PIPE_OUT;
	u3->fd = -1;
	u3->cmd_index = 0;

	// ── CMD 1 : cat > outfile ──────────────────────────────────────────────
	t_pipe_unit *u4 = calloc(1, sizeof(t_pipe_unit));
	u4->type = PIPE_IN;
	u4->fd = -1;
	u4->cmd_index = 1;

	t_pipe_unit *u5 = calloc(1, sizeof(t_pipe_unit));
	u5->type = CMD;
	u5->args = malloc(2 * sizeof(char *));
	u5->args[0] = ft_strdup("cat");
	u5->args[1] = NULL;
	u5->fd = -1;
	u5->cmd_index = 1;

	t_pipe_unit *u6 = calloc(1, sizeof(t_pipe_unit));
	u6->type = REDIR_OUT;
	u6->file = ft_strdup("outfile");
	u6->fd = -1;
	u6->cmd_index = 1;

	// ── Chain ────────────────────────────────────────────────────────────
	u1->next = u2;
	u2->next = u3;
	u3->next = u4;
	u4->next = u5;
	u5->next = u6;
	u6->next = NULL;

	mini->units = u1;
	mini->pipe_nb = 1;
}

void	print_data(t_mini *mini)
{
	t_pipe_unit	*curr;
	int			node;
	int			j;

	node = 0;
	curr = mini->units;
	while (curr)
	{
		ft_printf("── node[%d] ──────────────────────────────\n", node);
		ft_printf("  type     : %d\n", curr->type);
		ft_printf("  cmd_index: %d\n", curr->cmd_index);
		if (curr->args)
		{
			j = 0;
			while (curr->args[j])
			{
				ft_printf("  args[%d]  : %s\n", j, curr->args[j]);
				j++;
			}
		}
		if (curr->file)
			ft_printf("  file     : %s\n", curr->file);
		ft_printf("  fd       : %d\n", curr->fd);
		node++;
		curr = curr->next;
	}
	ft_printf("─────────────────────────────────────────\n");
}

int	execute_input(t_mini *mini)
{
	init_data(mini);
	mini->cmd_nb = mini->pipe_nb + 1;
	mini->envp = build_envp_tab(mini->env);
	if (!mini->envp)
		print_error_and_exit(mini, ERR_ALLOC, EXIT_FAILURE);
	if (!execute_heredocs(mini))
		return (0);
	if (mini->pipe_nb && !create_pipes(mini))
		return (0);
	if (!create_children(mini))
		return (0);
	if (!wait_children(mini))
		return (0);
	return (1);
}

static char	**build_envp_tab(t_env *env)
{
	char	**envp;
	char	*temp;
	int		i;
	int		env_nodes;

	env_nodes = count_env_nodes(env);
	envp = malloc((env_nodes + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		if (!temp)
			return (free_char_tab(envp), NULL);
		envp[i] = ft_strjoin(temp, env->value);
		free(temp);
		if (!envp[i])
			return (free_char_tab(envp), NULL);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
