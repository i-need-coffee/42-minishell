#include "minishell.h"

void	init_data(t_mini *mini)
{
	// cat << EOA << EOB | grep "error" | sort -u << EOC >> final.txt

	// ── CMD 1 : cat << EOA << EOB ────────────────────────────────────────
	t_pipe_unit *u1 = calloc(1, sizeof(t_pipe_unit));
	u1->type = CMD;
	u1->value = ft_strdup("cat");
	u1->fd = -1;
	u1->cmd_index = 0;

	t_pipe_unit *u2 = calloc(1, sizeof(t_pipe_unit));
	u2->type = HEREDOC;
	u2->value = ft_strdup("EOA");
	u2->fd = -1;
	u2->cmd_index = 0;

	t_pipe_unit *u3 = calloc(1, sizeof(t_pipe_unit));
	u3->type = HEREDOC;
	u3->value = ft_strdup("EOB");
	u3->fd = -1;
	u3->cmd_index = 0;

	// ── PIPE ─────────────────────────────────────────────────────────────
	t_pipe_unit *u4 = calloc(1, sizeof(t_pipe_unit));
	u4->type = PIPE;
	u4->value = NULL;
	u4->fd = -1;
	u4->cmd_index = 0;

	// ── CMD 2 : grep "error" ─────────────────────────────────────────────
	t_pipe_unit *u5 = calloc(1, sizeof(t_pipe_unit));
	u5->type = CMD;
	u5->value = ft_strdup("grep error");
	u5->fd = -1;
	u5->cmd_index = 1;

	// ── PIPE ─────────────────────────────────────────────────────────────
	t_pipe_unit *u6 = calloc(1, sizeof(t_pipe_unit));
	u6->type = PIPE;
	u6->value = NULL;
	u6->fd = -1;
	u6->cmd_index = 1;

	// ── CMD 3 : sort -u << EOC >> final.txt ──────────────────────────────
	t_pipe_unit *u7 = calloc(1, sizeof(t_pipe_unit));
	u7->type = CMD;
	u7->value = ft_strdup("sort -u");
	u7->fd = -1;
	u7->cmd_index = 2;

	t_pipe_unit *u8 = calloc(1, sizeof(t_pipe_unit));
	u8->type = HEREDOC;
	u8->value = ft_strdup("EOC");
	u8->fd = -1;
	u8->cmd_index = 2;

	t_pipe_unit *u9 = calloc(1, sizeof(t_pipe_unit));
	u9->type = APPEND;
	u9->value = ft_strdup("final.txt");
	u9->fd = -1;
	u9->cmd_index = 2;

	// ── Chain ─────────────────────────────────────────────────────────────
	u1->next = u2;
	u2->next = u3;
	u3->next = u4;
	u4->next = u5;
	u5->next = u6;
	u6->next = u7;
	u7->next = u8;
	u8->next = u9;
	mini->units = u1;
}

int	execute_input(t_mini *mini)
{
	init_data(mini);
	if (!execute_heredocs(mini))
		return (0);
	print_data(mini);
	return (1);
}
