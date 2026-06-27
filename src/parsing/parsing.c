#include "minishell.h"

int add_arg(char *str, int i, t_pipe_unit *unit, int ai)
{
    int start;

    start = i;
    while(str[i] && (str[i] != ' ' || str[i] == '\'' || str[i] == '\"'))
    {
        i++;
    }
    unit->args[ai] = ft_substr(str, start, i- start);
    return(i);
}

int handle_quote(char *str, int i, int ai)
{
    (void)str;
    (void)i;
    (void)ai;
    return (0);
}

int    parse_word_token(char *str, t_pipe_unit **unit, int cmdi)
{
    int i;
    int ai;
    t_pipe_unit *new_token;
    (void)unit;

    new_token = malloc(sizeof(t_pipe_unit));
    if(!new_token)
    {
        perror("Error allocation :");
        exit(EXIT_FAILURE);
    }
    new_token->type = CMD;
    new_token->file = NULL;
    new_token->fd = -1;
    new_token->cmd_index = cmdi;
    i = 0;
    ai = 0;
    while(str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            i += handle_quote(str, i, ai);
            ai++;
        }
        else
        {
            // i = add_arg(str, i, new_token, ai);
            new_token->args[ai] = ft_substr("echo lala", 0, 4);
            ai++;
        }
        while(str[i] == ' ')
            i++;
        exit(1);
        ft_printf("%d\n", i);
    }
    return (i);
}

void	parse_tokens(t_mini *mini)
{
    t_token	*current;
    t_pipe_unit *unit;
    int   ret;
    int     cmdi;

    cmdi = 0;

    current = mini->tokens;
    while (current->type != TOKEN_EOF)
    {
        if (current->type == TOKEN_WORD)
            ret = parse_word_token(current->value, &unit, cmdi);
        // else if (current->type == TOKEN_PIPE)
        //     ret = parse_pipe_token(current);
        // else if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
        //          || current->type == TOKEN_APPEND || current->type == TOKEN_HEREDOC)
        //     ret =parse_redirection_token(current);
        if (ret == -1)
        {
            return; //todo: handle error
        }
        cmdi++;
        current = current->next;
    }
}
