/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:08:07 by fdevigne          #+#    #+#             */
/*   Updated: 2022/07/27 15:35:42 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Print current location in the system.

void	ft_pwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!env)
		return ;
	while (tmp)
	{
        if (!ft_strncmp(tmp->key, "PWD", 3))
        {
		    printf("%s\n", tmp->value);
            return ;
        }
        tmp = tmp->next;
	}
}