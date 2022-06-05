/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:52:23 by jvalenci          #+#    #+#             */
/*   Updated: 2022/05/30 14:54:11 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* return the last node in a liked-list */
t_env	*ft_last_node(t_env *head)
{
	t_env	*tmp;

	if (!head)
		return (0);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}