#include "minishell.h"

int strlen_key(char *envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (envp[i] == '=')
            return (i);
        i++;
    }
    return (0);
}

t_env   **build_env(char **envp, t_env **env)
{
    int i;
    t_env   *node;
    int     len_key;

    i = 0;   
    while(envp[i])
    {
        len_key = strlen_key(envp[i]);
        node = new_node();
        if (!node)
            return (0);
        node->key = ft_substr(envp[i], 0, len_key);
        node->value = ft_substr(envp[i], len_key + 1, ft_strlen(envp[i]) - len_key);
        add_back(env, node);
//        print_node_env(node); - Pour regarder si l'implementation cest bien passe.
        i++;
    }
    return (env);
}
