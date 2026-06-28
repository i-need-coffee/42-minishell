#include "minishell.h"

int parse_tokens(t_mini *mini, t_pipe_unit **unit)
{
    t_token	*current;
    // t_pipe_unit *unit;
    int     cmdi;

    cmdi = 0;
    current = mini->tokens;
    *unit = NULL;
    while (current->type != TOKEN_EOF)
    {
        if (current->type == TOKEN_WORD)
            if(parse_word_token(unit, current->value, cmdi, mini->env) < 0)
                return (-1);
        // else if (current->type == TOKEN_PIPE)
        //     ret = parse_pipe_token(current);
        // else if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
        //          || current->type == TOKEN_APPEND || current->type == TOKEN_HEREDOC)
        //     ret =parse_redirection_token(current);
        if (*unit == NULL)
        {
            return (-1); //todo: handle error
        }
        cmdi++;
        current = current->next;
    }
    if (*unit && (*unit)->args)
        ft_lstiter((*unit)->args, &print_lst);
    return (0);
}
