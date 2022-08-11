/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:33:23 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/11 19:19:28 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Before unsetting the variable, where making sure that
// It's name (the key) is a valid one

static void	ft_freeone_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

// The actual deletion of the variable(s)

void	ft_del_env(t_env **env, char *key)
{
	t_env	*before;
	t_env	*tmp;

	before = NULL;
	tmp = *env;
	while (tmp && !ft_strequ(tmp->key, key))
	{
		before = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	if (!before)
	{
		*env = tmp->next;
		ft_freeone_env(tmp);
		return ;
	}
	before->next = tmp->next;
	ft_freeone_env(tmp);
}


int	ft_unset(char **argv, t_env **env)
{
	char	*key;

	if (!argv[1])
		return (0);
	key = argv[1];
	if (!ft_is_valid_key(key))
	{
		ft_putstr_fd("Invalid key name.\n", 1);
		return (1);
	}
	ft_del_env(env, key);
	return (0);
}
