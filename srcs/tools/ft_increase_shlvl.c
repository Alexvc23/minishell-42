/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_increase_shlvl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvalenci <jvalenci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:48:26 by fdevigne          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/18 11:59:19 by fdevigne         ###   ########.fr       */
=======
/*   Updated: 2022/08/18 11:35:56 by jvalenci         ###   ########.fr       */
>>>>>>> test
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
=======
int	ft_counter(t_cmd	*cmd)
{
	int				i;

	i = -1;
	while (cmd->argv[++i] && cmd->argv[i + 1])
		;
	return (i);
}
>>>>>>> test
int	ft_increase_shlvl(t_env	*env)
{
	while (env->next && ft_strcmp2(env->key, "SHLVL"))
		env = env->next;
	if (!ft_strcmp2(env->key, "SHLVL"))
		return (ft_atoi(env->value) + 1);
	return (1);
}
<<<<<<< HEAD
=======

>>>>>>> test
