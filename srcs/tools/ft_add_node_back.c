/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:47:50 by jvalenci          #+#    #+#             */
/*   Updated: 2022/05/30 14:55:04 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* we append a new node to the end of the linked-list */
void	ft_add_node_back(t_env **head, t_env *new)
{
	t_env	*ptr;

	ptr = *head;
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	ptr = ft_last_node(*head);
	ptr->next = new;
}
