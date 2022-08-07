/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:06:46 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/06 17:22:18 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
Turns t_env linked list to 2d array 
*/
char **ft_env_to_array(t_env **env)
{
    char    **arr;
    t_env   *tmp;
    size_t  envsize;
    size_t  i;

    envsize = ft_size_list(g_vars->env);
    arr = malloc(sizeof(char *) * envsize + 1);
    arr[envsize] = NULL;
    if (!envsize)
        return (arr);
    i = 0; 
    tmp = *env;
    while (tmp)
    {
        arr[i++] = ft_env_join(tmp->key, tmp->value);
        tmp = tmp->next;
    }
    return (arr);
}