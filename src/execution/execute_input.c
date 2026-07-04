#include "minishell.h"

static char **build_envp_tab(t_env *env);

void	init_data(t_mini *mini)
{
	// < infile cat | grep "error" | sort -u << EOF >> outfile

	// ── CMD 1 : < infile cat ─────────────────────────────────────────────
	t_pipe_unit *u1 = calloc(1, sizeof(t_pipe_unit));
	u1->type = REDIR_IN;
	u1->file = ft_strdup("infile");
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

	// ── CMD 2 : PIPE_IN grep "error" PIPE_OUT ────────────────────────────
	t_pipe_unit *u4 = calloc(1, sizeof(t_pipe_unit));
	u4->type = PIPE_IN;
	u4->fd = -1;
	u4->cmd_index = 1;

	t_pipe_unit *u5 = calloc(1, sizeof(t_pipe_unit));
	u5->type = CMD;
	u5->args = malloc(3 * sizeof(char *));
	u5->args[0] = ft_strdup("grep");
	u5->args[1] = ft_strdup("error");
	u5->args[2] = NULL;
	u5->fd = -1;
	u5->cmd_index = 1;

	t_pipe_unit *u6 = calloc(1, sizeof(t_pipe_unit));
	u6->type = PIPE_OUT;
	u6->fd = -1;
	u6->cmd_index = 1;

	// ── CMD 3 : PIPE_IN sort -u << EOF >> outfile ────────────────────────
	t_pipe_unit *u7 = calloc(1, sizeof(t_pipe_unit));
	u7->type = PIPE_IN;
	u7->fd = -1;
	u7->cmd_index = 2;

	t_pipe_unit *u8 = calloc(1, sizeof(t_pipe_unit));
	u8->type = CMD;
	u8->args = malloc(3 * sizeof(char *));
	u8->args[0] = ft_strdup("sort");
	u8->args[1] = ft_strdup("-u");
	u8->args[2] = NULL;
	u8->fd = -1;
	u8->cmd_index = 2;

	t_pipe_unit *u9 = calloc(1, sizeof(t_pipe_unit));
	u9->type = HEREDOC;
	u9->file = ft_strdup("EOF");
	u9->fd = -1;
	u9->cmd_index = 2;

	t_pipe_unit *u10 = calloc(1, sizeof(t_pipe_unit));
	u10->type = APPEND;
	u10->file = ft_strdup("outfile");
	u10->fd = -1;
	u10->cmd_index = 2;

	// ── Chain ────────────────────────────────────────────────────────────
	u1->next = u2;
	u2->next = u3;
	u3->next = u4;
	u4->next = u5;
	u5->next = u6;
	u6->next = u7;
	u7->next = u8;
	u8->next = u9;
	u9->next = u10;
	u10->next = NULL;

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
	mini->cmd_nb = mini->pipe_nb + 1;
	mini->envp = build_envp_tab(mini->env);
	if (!mini->envp)
		print_error_and_exit(mini, ERR_ALLOC, 1);
	init_data(mini);
	if (!execute_heredocs(mini))
		return (0);
	if (mini->pipe_nb && !create_pipes(mini))
		return (0);
/* 	if (!create_children(mini))
		return (0); */
	execute_cmd(mini);
	return (1);
}

static char **build_envp_tab(t_env *env)
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
