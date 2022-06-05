/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_node_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:43:59 by jvalenci          #+#    #+#             */
/*   Updated: 2022/06/01 14:54:12 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* Return the value of the key passed as argument, the value will be
 an envinonment variable store in the t_env structure */
char *ft_get_node_value(t_env **head, char *key)
{
    t_env *tmp;

    tmp = *head;
    if (!*head)
        return (NULL);
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}