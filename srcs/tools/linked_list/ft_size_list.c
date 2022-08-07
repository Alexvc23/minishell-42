/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:02:08 by jvalenci          #+#    #+#             */
/*   Updated: 2022/08/07 16:54:41 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* we count the number of nodes in a linked list passing as argumet its head */
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

// A second one that works with cmd
int	ft_size_list2(t_cmd *cmd)
{
	int		count;
	t_cmd	*ptr;

	if (!cmd)
		return (0);
	ptr = cmd;
	count = 0;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}