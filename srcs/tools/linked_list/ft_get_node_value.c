/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_node_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:43:59 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/13 15:57:34 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* 
Return the value address of the key passed as argument, the value will be
an envinonment variable store in the t_env structure
*/
char	*ft_get_node_value(t_env **head, char *key)
{
	t_env	*tmp;

	tmp = *head;
	if (!*head)
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp2(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
