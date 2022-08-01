/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:02:08 by jvalenci          #+#    #+#             */
/*   Updated: 2022/07/29 10:06:01 by fdevigne         ###   ########.fr       */
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