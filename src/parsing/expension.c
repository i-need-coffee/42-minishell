#include "minishell.h"

int    handle_dollard(char *str, int i, t_env *env, char **buffer)
{
    int end;
    char    *key;
    t_env   *temp;
    char    *tmp_buffer;

    temp = env;
    i++;
    end = i;
    tmp_buffer = (char*)malloc(ft_strlen(*buffer) + 1);
    while(ft_isalnum(str[end]))
        end++;
    key = ft_substr(str, i, end - i);
    while (temp)
    {
        if(!ft_strncmp(key, temp->key, end))
        {
            ft_strlcpy(tmp_buffer, *buffer, (ft_strlen(*buffer) + 1));
            free(*buffer);
            *buffer = ft_strjoin(tmp_buffer, temp->value);
            free(key);
            free(tmp_buffer);
            return end;
        }
        temp= temp->next;
    }
    free(key);
    free(tmp_buffer);
    return end;
}

