#include "minishell.h"

void	init_data(t_mini *mini)
{
	// < infile cat | grep "error" | sort -u << EOF >> outfile

	// ── CMD 1 : < infile cat ─────────────────────────────────────────────
	t_pipe_unit *u1 = calloc(1, sizeof(t_pipe_unit));
	u1->type = REDIR_IN;
	u1->args = NULL;
	u1->file = ft_strdup("infile");
	u1->fd = -1;
	u1->cmd_index = 0;

	t_pipe_unit *u2 = calloc(1, sizeof(t_pipe_unit));
	u2->type = CMD;
	u2->args = malloc(2 * sizeof(char *));
	u2->args[0] = ft_strdup("cat");
	u2->args[1] = NULL;
	u2->file = NULL;
	u2->fd = -1;
	u2->cmd_index = 0;

	// ── CMD 2 : grep "error" ─────────────────────────────────────────────
	t_pipe_unit *u3 = calloc(1, sizeof(t_pipe_unit));
	u3->type = CMD;
	u3->args = malloc(3 * sizeof(char *));
	u3->args[0] = ft_strdup("grep");
	u3->args[1] = ft_strdup("error");
	u3->args[2] = NULL;
	u3->file = NULL;
	u3->fd = -1;
	u3->cmd_index = 1;

	// ── CMD 3 : sort -u << EOC >> final.txt ──────────────────────────────
	t_pipe_unit *u4 = calloc(1, sizeof(t_pipe_unit));
	u4->type = CMD;
	u4->args = malloc(3 * sizeof(char *));
	u4->args[0] = ft_strdup("sort");
	u4->args[1] = ft_strdup("-u");
	u4->args[2] = NULL;
	u4->file = NULL;
	u4->fd = -1;
	u4->cmd_index = 2;

	t_pipe_unit *u5 = calloc(1, sizeof(t_pipe_unit));
	u5->type = HEREDOC;
	u5->args = NULL;
	u5->file = ft_strdup("EOF");
	u5->fd = -1;
	u5->cmd_index = 2;

	t_pipe_unit *u6 = calloc(1, sizeof(t_pipe_unit));
	u6->type = APPEND;
	u6->args = NULL;
	u6->file = ft_strdup("outfile");
	u6->fd = -1;
	u6->cmd_index = 2;

	// ── Chain ─────────────────────────────────────────────────────────────
	u1->next = u2;
	u2->next = u3;
	u3->next = u4;
	u4->next = u5;
	u5->next = u6;
	u6->next = NULL;
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
	if (!execute_heredocs(mini))
		return (0);
	open_files(mini->units);
	print_data(mini);
	return (1);
}
