/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_key_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdevigne <fdevigne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:54:47 by fdevigne          #+#    #+#             */
/*   Updated: 2022/08/17 18:15:06 by fdevigne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_env_size(t_env **env)
{
	t_env	*tmp;
	size_t	size;

	if (!env || !*env)
		return (0);
	size = 0;
	tmp = *env;
	while (tmp && ++size)
		tmp = tmp->next;
	return (size);
}

char	**ft_env_to_key_array(t_env **env)
{
	char	**arr;
	t_env	*tmp;
	size_t	env_size;
	size_t	i;

	env_size = ft_env_size(env);
	arr = malloc(sizeof(char *) * (env_size + 1));
	arr[env_size] = NULL;
	if (!env_size)
		return (arr);
	i = 0;
	tmp = *env;
	while (tmp)
	{
		arr[i++] = ft_strdup(tmp->key);
		tmp = tmp->next;
	}
	return (arr);
}
