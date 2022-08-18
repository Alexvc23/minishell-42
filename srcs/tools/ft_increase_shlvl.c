/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_increase_shlvl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:48:26 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/18 11:35:56 by jvalenci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_counter(t_cmd	*cmd)
{
	int				i;

	i = -1;
	while (cmd->argv[++i] && cmd->argv[i + 1])
		;
	return (i);
}
int	ft_increase_shlvl(t_env	*env)
{
	while (env && ft_strcmp2(env->key, "SHLVL"))
		env = env->next;
	if (!ft_strcmp2(env->key, "SHLVL"))
		return (ft_atoi(env->value) + 1);
	return (1);
}

