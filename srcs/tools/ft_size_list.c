/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:02:08 by jvalenci          #+#    #+#             */
/*   Updated: 2022/05/30 12:02:12 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* we count the number of node in a linked list passing as argumet its head */
int	ft_size_list(t_env *head)
{
	int		count;
	t_env	*ptr;

	if (!head)
		return (0);
	ptr = head;
	count = 0;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}