#include "minishell.h"

static char	**build_envp_tab(t_env *env);

void	init_data(t_mini *mini)
{
	t_pipe_unit	*u1;
	t_pipe_unit	*u2;
	t_pipe_unit	*u3;
	t_pipe_unit	*u4;
	t_pipe_unit	*u5;
	t_pipe_unit	*u6;
	t_pipe_unit	*u7;
	t_pipe_unit	*u8;
	t_pipe_unit	*u9;

	// cat
	u1 = calloc(1, sizeof(t_pipe_unit));
	u1->type = CMD;
	u1->args = malloc(sizeof(char *) * 2);
	u1->args[0] = ft_strdup("cat");
	u1->args[1] = NULL;
	u1->fd = -1;
	u1->cmd_index = 0;

	// < infile
	u2 = calloc(1, sizeof(t_pipe_unit));
	u2->type = REDIR_IN;
	u2->file = ft_strdup("infile");
	u2->fd = -1;
	u2->cmd_index = 0;

	// |
	u3 = calloc(1, sizeof(t_pipe_unit));
	u3->type = PIPE_OUT;
	u3->fd = -1;
	u3->cmd_index = 0;

	u4 = calloc(1, sizeof(t_pipe_unit));
	u4->type = PIPE_IN;
	u4->fd = -1;
	u4->cmd_index = 1;

	// echo hello
	u5 = calloc(1, sizeof(t_pipe_unit));
	u5->type = CMD;
	u5->args = malloc(sizeof(char *) * 3);
	u5->args[0] = ft_strdup("grep");
	u5->args[1] = ft_strdup("hello");
	u5->args[2] = NULL;
	u5->fd = -1;
	u5->cmd_index = 1;

	// |
	u6 = calloc(1, sizeof(t_pipe_unit));
	u6->type = PIPE_OUT;
	u6->fd = -1;
	u6->cmd_index = 1;

	u7 = calloc(1, sizeof(t_pipe_unit));
	u7->type = PIPE_IN;
	u7->fd = -1;
	u7->cmd_index = 2;

	// cat
	u8 = calloc(1, sizeof(t_pipe_unit));
	u8->type = CMD;
	u8->args = malloc(sizeof(char *) * 2);
	u8->args[0] = ft_strdup("cat");
	u8->args[1] = NULL;
	u8->fd = -1;
	u8->cmd_index = 2;

	// > outfile
	u9 = calloc(1, sizeof(t_pipe_unit));
	u9->type = REDIR_OUT;
	u9->file = ft_strdup("outfile");
	u9->fd = -1;
	u9->cmd_index = 2;

	u1->next = u2;
	u2->next = u3;
	u3->next = u4;
	u4->next = u5;
	u5->next = u6;
	u6->next = u7;
	u7->next = u8;
	u8->next = u9;
	u9->next = NULL;

	mini->units = u1;
	mini->pipe_nb = 2;
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
