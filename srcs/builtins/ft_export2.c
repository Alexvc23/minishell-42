/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:28:11 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/11 17:48:57 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exists(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	ft_replace(t_env **env, char *key, char *new_val)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	free(tmp->value);
	free(key);
	tmp->value = new_val;
}

void	ft_set_env2(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	if (ft_exists(env, key))
	{
		ft_replace(env, key, value);
		return ;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->next = NULL;
	tmp = *env;
	if (!tmp)
	{
		*env = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	*ft_get_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strequ(key, env->key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

void	ft_afree(void **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}