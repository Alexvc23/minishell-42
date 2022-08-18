/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_increase_shlvl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:48:26 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/17 18:20:18 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_increase_shlvl(t_env	*env)
{
	while (env && ft_strcmp2(env->key, "SHLVL"))
		env = env->next;
	if (!ft_strcmp2(env->key, "SHLVL"))
		return (ft_atoi(env->value) + 1);
	return (1);
}
