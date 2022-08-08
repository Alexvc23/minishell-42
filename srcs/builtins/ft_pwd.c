/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:08:07 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/08 17:34:42 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Print current location in the system.

int	ft_pwd(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!env)
		return (1);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 3))
		{
			printf("%s\n", tmp->value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
