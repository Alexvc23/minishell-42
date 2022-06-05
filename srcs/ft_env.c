#include"minishell.h"

/* print environement variables stored in t_env struct*/
void ft_env(t_env *env)
{
    t_env *tmp;

    tmp = env;
    if (!env)
        return;
    while (tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}